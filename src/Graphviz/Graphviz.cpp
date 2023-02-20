#include "Graphviz.hpp"

std::vector<GraphvizLogger*> g_loggers;
std::vector<Location_t> g_locations;

void addLogger(GraphvizLogger* logger) {
    for (size_t it = 0; it < g_locations.size(); ++it) {
        logger->startEnv(g_locations[it]);
    }
    g_loggers.push_back(logger);
}

GraphvizEnvTracker::GraphvizEnvTracker(Location_t location) {
    std::cout << "cur_loc: " << location.file << ":" << location.line << ":" << location.func << std::endl;
    g_locations.push_back(location);
    for (auto logger : g_loggers) {
        logger->startEnv(location);
    }
}

GraphvizEnvTracker::~GraphvizEnvTracker() {
    for (auto logger : g_loggers) {
        logger->stopEnv();
    }
    g_locations.pop_back();
}

GraphvizLogger::~GraphvizLogger() {
    // fprintf(Graphviz_OUT_FILE, "subgraph caption {\n"
    //                        "label=\"...\"\n"
    //                        "COPIES [label=\"COPY_COUNT=%d\"]\n"
    //                        "}\n",
    for (auto &s : m_links) {
        fprintf(m_file, "%s", s.c_str());
    }
    fprintf(m_file, "}\n");
    fclose(m_file);
    std::string cmd_str = "dot " + m_filename + " -Tpng -o " + m_filename + ".png";
    system(cmd_str.c_str());
}


GraphvizLogger::GraphvizLogger(std::string filename) {
    m_file = fopen(filename.c_str(), "w");
    if (m_file == NULL) {
        throw std::runtime_error("Failed to open file");
    }
    m_filename = filename;
    fprintf(m_file, "digraph G {\n"
                    "node [shape=record];\n"
                    "fontname=\"Roboto Mono\"\n");
    addLogger(this);
}

void GraphvizLogger::startEnv(Location_t location)
{
    m_cluster_count++;

    fprintf(m_file, "subgraph cluster%d {\n"
                               "color=black\n"
                               "style=filled\n"
                               "fillcolor=\"#00000010\"\n"
                               "label=\"%s:%s():%d\"\n",
                               m_cluster_count, location.file, location.func, location.line);
}

void GraphvizLogger::stopEnv()
{
    fprintf(m_file, "}\n");
}

int GraphvizLogger::createOperationNode(const Graph_object_t &first,
                                        const Graph_object_t &second,
                                        const Graph_object_t &result,
                                        const char *operation)
{
    static int operation_count = 0;
    operation_count++;

    fprintf(m_file, "op%d [color=blue, shape=circle, label=\"%s\"]\n",
            operation_count, operation);

    createOrientedEdge(first, ("op" + std::to_string(operation_count)).c_str(), "blue");
    createOrientedEdge(second, ("op" + std::to_string(operation_count)).c_str(), "blue");
    createOrientedEdge(("op" + std::to_string(operation_count)).c_str(), result, "blue");

    return operation_count;
}

int GraphvizLogger::createModificationNode(Graph_object_t &modified,
                                           const Graph_object_t &second,
                                           const char *operation)
{
    static int operation_count = 0;
    operation_count++;

    fprintf(m_file, "op%d [color=blue, shape=circle, label=\"%s\"]\n",
            operation_count, operation);
    modified.version--;
    createOrientedEdge(modified, ("op" + std::to_string(operation_count)).c_str(), "blue");
    createOrientedEdge(second, ("op" + std::to_string(operation_count)).c_str(), "blue");
    modified.version++;
    createNode(&modified, "darkgreen");
    createOrientedEdge(("op" + std::to_string(operation_count)).c_str(), modified, "blue");

    return operation_count;
}

void GraphvizLogger::createNode(const Graph_object_t* obj,
                                const char *color)
{
    
    fprintf(m_file,     "%s [color=%s, label=\"{var_name=\'%s\'|value=%s|address=%p|id=%llu}\"]\n",
            obj->get_unique_name().c_str(), color, obj->var_name.c_str(), obj->get_value().c_str(), obj, obj->graph_id);
}

void GraphvizLogger::createOrientedEdge(const Graph_object_t &from,
                                        const Graph_object_t &to, 
                                        const char *color,
                                        const char *label,
                                        const char *label_color)
{
    std::stringstream stream;
    stream << from.get_unique_name() << " -> " << to.get_unique_name() << " [color=" << color << ", label=\"" << label  << "\", fontcolor=\"" << label_color << "\"]\n";
    m_links.push_back(stream.str());
    // fprintf(m_file, "%s -> %s [color=%s, label=\"%s\", fontcolor=\"%s\"]\n",
    //         from.get_unique_name().c_str(), to.get_unique_name().c_str(), color, label, label_color);
}

void GraphvizLogger::createOrientedEdge(const Graph_object_t &from,
                                        const char *to,
                                        const char *color,
                                        const char *label,
                                        const char *label_color)
{
    std::stringstream stream;
    stream << from.get_unique_name() << " -> " << to << " [color=" << color << ", label=\"" << label  << "\", fontcolor=\"" << label_color << "\"]\n";
    m_links.push_back(stream.str());
    // fprintf(m_file, "%s -> %s [color=%s, label=\"%s\", fontcolor=\"%s\"]\n",
    //         from.get_unique_name().c_str(), to, color, label, label_color);
}

void GraphvizLogger::createOrientedEdge(const char* from,
                                        const Graph_object_t &to,
                                        const char *color,
                                        const char *label,
                                        const char *label_color)
{
    std::stringstream stream;
    stream << from << " -> " << to.get_unique_name() << " [color=" << color << ", label=\"" << label  << "\", fontcolor=\"" << label_color << "\"]\n";
    m_links.push_back(stream.str());
    // fprintf(m_file, "%s -> %s [color=%s, label=\"%s\", fontcolor=\"%s\"]\n",
    //         from, to.get_unique_name().c_str(), color, label, label_color);
}
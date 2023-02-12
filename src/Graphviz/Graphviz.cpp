#include "Graphviz.hpp"

void GraphvizLogger::startEnv(Location_t location)
{
    static int cluster_count = 0;
    cluster_count++;

    fprintf(m_file, "subgraph cluster%d {\n"
                               "color=orange\n"
                               "label=\"%s:%d %s()\"\n",
            cluster_count, location.file, location.line, location.func);
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

void GraphvizLogger::createNode(Graph_object_t* obj,
                                const char *color)
{
    fprintf(m_file, "%s [color=%s, label=\"{name=\'%s\'|value=%d|address=%p}\"]\n",
            obj->name, color, obj->name, obj->name.c_str(), obj);
}

void GraphvizLogger::createOrientedEdge(const Graph_object_t &from,
                                        const Graph_object_t &to, 
                                        const char *color,
                                        const char *label,
                                        const char *label_color)
{
    fprintf(m_file, "%s -> %s [color=%s, label=\"%s\", fontcolor=\"%s\"]\n",
            from.name(), to.name(), color, label, label_color);
}

void GraphvizLogger::createOrientedEdge(const Graph_object_t &from,
                                        const char *to,
                                        const char *color,
                                        const char *label,
                                        const char *label_color)
{
    fprintf(m_file, "%s -> %s [color=%s, label=\"%s\", fontcolor=\"%s\"]\n",
            from.name, to, color, label, label_color);
}

void GraphvizLogger::createOrientedEdge(const char *from,
                                 const Graph_object_t &to,
                                 const char *color,
                                 const char *label,
                                 const char *label_color)
{
    fprintf(m_file, "%s -> %s [color=%s, label=\"%s\", fontcolor=\"%s\"]\n",
            from, to.name(), color, label, label_color);
}
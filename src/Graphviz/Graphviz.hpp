#ifndef GRAPHVIZ_HPP
#define GRAPHVIZ_HPP

#include <cstdio>
#include <string>
#include <stdexcept>
#include "Location.hpp"

struct Graph_object_t {
    std::string name;
    std::string value;
    std::string type;
    std::string color;
    std::string label;
    std::string label_color;
};

class GraphvizLogger {
public:
    GraphvizLogger(std::string filename) {
        m_file = fopen(filename.c_str(), "w");
        if (m_file == NULL) {
            throw std::runtime_error("Failed to open file");
        }
        m_filename = filename;
        fprintf(m_file, "digraph G {\n"
                        "node [shape=record];\n"
                        "fontname=\"Roboto Mono\"\n");
    }

    GraphvizLogger(const GraphvizLogger&) = delete;
    GraphvizLogger(GraphvizLogger&&) = default;

    void startEnv(Location_t location);
    void stopEnv ();

    void createNode(const Graph_object_t& obj, const char* color = "black");

    void createUnorientedEdge(const Graph_object_t& num, 
                              const char* operation, 
                              const char* color);

    int  createOperationNode(const Graph_object_t& first, 
                             const Graph_object_t& second, 
                             const Graph_object_t& result, 
                             const char* operation);

    void createOrientedEdge(const Graph_object_t& from, 
                            const Graph_object_t& to, 
                            const char* color,
                            const char* label = "", 
                            const char* label_color = "");

    void createOrientedEdge(const Graph_object_t& from, 
                            const char* to, 
                            const char* color, 
                            const char* label = "", 
                            const char* label_color = "");

    void createOrientedEdge(const char* from, 
                                     const Graph_object_t& to, 
                                     const char* color, 
                                     const char* label = "", 
                                     const char* label_color = "");

    ~GraphvizLogger() {
        fprintf(m_file, "}\n");
        fclose(m_file);
        std::string cmd_str = "dot " + m_filename + " -Tpng -o " + m_filename + ".png";
        system(cmd_str.c_str());
    }

private:
    FILE*       m_file;
    std::string m_filename;
    int         m_cluster_count = 0;
};


#endif // GRAPHVIZ_HPP
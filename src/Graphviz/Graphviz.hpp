#ifndef GRAPHVIZ_HPP
#define GRAPHVIZ_HPP

#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>
#include "Location.hpp"

class GraphvizLogger;




void addLogger(GraphvizLogger* logger);

class GraphvizEnvTracker {
public:
    GraphvizEnvTracker(Location_t location);

    ~GraphvizEnvTracker();
};


struct Graph_object_t {
    std::string class_name = "";
    std::string var_name;
    size_t      graph_id   = 0;
    size_t      version    = 0;
    std::string   get_unique_name() const {
        return (var_name + std::string("_") + std::to_string(graph_id) + std::string("_") + std::to_string(version));
    }
    virtual std::string get_value() const = 0;
};

class GraphvizLogger {
public:
    GraphvizLogger(std::string filename);

    GraphvizLogger(const GraphvizLogger&) = delete;
    GraphvizLogger(GraphvizLogger&&) = default;
    
    ~GraphvizLogger();

    void startEnv(Location_t location);
    void stopEnv ();

    void createNode(const Graph_object_t* obj, const char* color = "black");

    void createUnorientedEdge(const Graph_object_t& num, 
                              const char* operation, 
                              const char* color);

    int  createOperationNode(const Graph_object_t& first, 
                             const Graph_object_t& second, 
                             const Graph_object_t& result, 
                             const char* operation);

    int  createModificationNode(Graph_object_t& modified, 
                                const Graph_object_t& second, 
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

    void createSubgraph(const char* name, const char* label);


private:
    FILE*       m_file;
    std::string m_filename;
    std::vector<std::string> m_links;
    int         m_cluster_count = 0;
};


#endif // GRAPHVIZ_HPP
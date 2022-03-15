#ifndef trees_graphs_h
#define trees_graphs_h

#include <vector>


class GNode {
    public:
        std::string name;
        std::vector<GNode*> nodes;
        bool is_visited;
    
    GNode(std::string name) : name(name), nodes(), is_visited(false) {}
};

class Graph {
    public:
        std::vector<GNode> nodes;
    Graph(std::vector<GNode> nodes) : nodes(nodes) {}
};


void run_trees_graphs();

//Exercises
const bool is_connected(Graph g, GNode* src, GNode* dst);

#endif /* trees_graphs_h */

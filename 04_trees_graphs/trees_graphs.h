#ifndef trees_graphs_h
#define trees_graphs_h

#include <vector>
#include <list>

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

class BNode {
    public:
        int number;
        BNode* left;
        BNode* right;
    BNode(int number) : number(number) {}
    BNode(int number, BNode* l, BNode* r) : number(number), left(l), right(r) {}
};

void run_trees_graphs();

//Exercises
const bool is_connected(Graph g, GNode* src, GNode* dst);
BNode* minimal_tree(const std::vector<int> v, int l, int r);
void list_of_depth(BNode* root, int level, std::vector<std::list<BNode*>>& depths);

#endif /* trees_graphs_h */

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
        std::vector<GNode*> nodes;
    Graph(std::vector<GNode*> nodes) : nodes(nodes) {}
};

class BNode {
    public:
        int number;
        BNode* left;
        BNode* right;
        BNode* parent;
    BNode(int number) : number(number) {}
    BNode(int number, BNode* l, BNode* r) : number(number), left(l), right(r) {}
};

void run_trees_graphs();

//Exercises
const bool is_connected(Graph g, GNode* src, GNode* dst);
BNode* minimal_tree(const std::vector<int> v, int l, int r);
void list_of_depth(BNode* root, int level, std::vector<std::list<BNode*>>& depths);
const bool is_balanced(const BNode* root, int* height);
const bool is_bst(const BNode* root, int min, int max);
const BNode* successor(const BNode* node);
void build_oder(Graph* g, std::vector<std::string>& order);
const BNode* first_common_ancestor(const BNode* root, const BNode* p, const BNode* q);
std::vector<std::list<int>> bst_sequences(const BNode* root);
const bool check_subtree(const BNode* a, const BNode* b);

#endif /* trees_graphs_h */

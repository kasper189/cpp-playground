#include <iostream>
#include <queue>
#include <stdio.h>

#include "trees_graphs.h"
#include "../common/common.h"

void reset_visited(Graph g) {
    for(GNode n : g.nodes) {
        n.is_visited = false;
    }
}

void in_order(BNode* node) {
    if(node == NULL) return;
    
    in_order(node->left);
    std::cout << "n: " << node->number << " | " ;
    in_order(node->right);
}

void run_trees_graphs() {
    std::cout << "Hello, Trees & Graphs!" << std::endl;
    
    // 4.1
    GNode a = GNode("a");
    GNode b = GNode("b");
    GNode c = GNode("c");
    GNode d = GNode("d");
    GNode e = GNode("e");
    a.nodes.push_back(&b);
    a.nodes.push_back(&c);
    b.nodes.push_back(&c);
    c.nodes.push_back(&d);
    std::vector<GNode> n;
    n.push_back(a);
    n.push_back(b);
    n.push_back(c);
    n.push_back(d);
    n.push_back(e);
    Graph g = Graph(n);
    std::cout << "is connected true is " << bool_as_text(is_connected(g, &a, &a)) << std::endl;
    reset_visited(g);
    std::cout << "is connected false is " << bool_as_text(is_connected(g, &a, &e)) << std::endl;

    // 4.2
    std::vector<int> f = {0, 1, 2, 3, 4, 5 , 6};
    BNode* h = minimal_tree(f, 0, 7);
    std::cout << "minimal tree 0 | 1 | 2 | 3 | 4 | 5 | 6 is" << std::endl;
    in_order(h);
    std::cout << std::endl;
    
}

/*4.1*/
const bool is_connected(Graph g, GNode* src, GNode* dst) {
    
    if(src == NULL || dst == NULL) return false;
    
    std::queue<GNode*> queue;
    queue.push(src);
    
    while(!queue.empty()) {
        GNode* node = queue.front();
        queue.pop();
        node->is_visited = true;
        if(node == dst) return true;
        for(GNode* n : node->nodes) {
            if(!n->is_visited) {
                queue.push(n);
            }
        }
    }
    
    return false;
}

/*4.2*/
BNode* minimal_tree(const std::vector<int> v, int l, int r) {
    if(r <= l) return NULL;
    
    int middle((l + r) / 2);
    BNode* node = new BNode(v[middle]);
    node->left = minimal_tree(v, l, middle);
    node->right = minimal_tree(v, middle + 1, r);
    
    return node;
}

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

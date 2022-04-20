#include <iostream>
#include <queue>
#include <stdio.h>
#include "trees_graphs.h"
#include "../common/common.h"

void reset_visited(Graph g) {
    for(GNode* n : g.nodes) {
        n->is_visited = false;
    }
}

void in_order(BNode* node) {
    if(node == NULL) return;
    
    in_order(node->left);
    std::cout << "n: " << node->number << " | " ;
    in_order(node->right);
}

void print_depths(const std::vector<std::list<BNode*>>& depths) {
    for(const std::list<BNode*>& l : depths){
        for(const BNode* n : l) {
            std::cout << n->number << "-" ;
        }
        std::cout << " | " ;
    }
    std::cout << std::endl;
}

void print_sequences(const std::vector<std::list<int>> sequences) {
    for(const std::list<int>& l : sequences){
        for(const int n : l) {
            std::cout << n << "-" ;
        }
        std::cout << " | " ;
    }
    std::cout << std::endl;
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
    std::vector<GNode*> n;
    n.push_back(&a);
    n.push_back(&b);
    n.push_back(&c);
    n.push_back(&d);
    n.push_back(&e);
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
    
    // 4.3
    BNode* aaaaa = new BNode(3, NULL, NULL);
    BNode* aaaa = new BNode(2, aaaaa, NULL);
    BNode* aaab = new BNode(2, NULL, NULL);
    BNode* aaba = new BNode(2, NULL, NULL);
    BNode* aabb = new BNode(2, NULL, NULL);
    BNode* aaa = new BNode(1, aaaa, aaab);
    BNode* aab = new BNode(1, aaba, aabb);
    BNode* aa = new BNode(0, aaa, aab);
    std::vector<std::list<BNode*>> depths;
    list_of_depth(aa, 0, depths);
    
    std::cout << "list of depths 0- | 1-1- | 2-2-2-2- | 3- is ";
    print_depths(depths);
    
    // 4.4
    int height(0);
    std::cout << "is balanced true is " << bool_as_text(is_balanced(aa, &height)) << std::endl;
    
    // 4.5
    std::cout << "is bst false is " << bool_as_text(is_bst(aa, INT_MIN, INT_MAX)) << std::endl;
    BNode* baaaa = new BNode(0, NULL, NULL);
    BNode* baaa = new BNode(1, baaaa, NULL);
    BNode* baab = new BNode(4, NULL, NULL);
    BNode* baba = new BNode(7, NULL, NULL);
    BNode* babb = new BNode(9, NULL, NULL);
    BNode* baa = new BNode(3, baaa, baab);
    BNode* bab = new BNode(8, baba, babb);
    BNode* ba = new BNode(5, baa, bab);
    std::cout << "is bst true is " << bool_as_text(is_bst(ba, INT_MIN, INT_MAX)) << std::endl;

    //4.6
    std::cout << "successor 7 is " << successor(ba)->number << std::endl;
    
    //4.7
    GNode ga = GNode("a");
    GNode gb = GNode("b");
    GNode gc = GNode("c");
    GNode gd = GNode("d");
    GNode ge = GNode("e");
    GNode gf = GNode("f");
    ga.nodes.push_back(&gd);
    gf.nodes.push_back(&gb);
    gb.nodes.push_back(&gd);
    gf.nodes.push_back(&ga);
    gd.nodes.push_back(&gc);
    std::vector<GNode*> nodes = { &ga, &gb, &gc, &gd, &ge, &gf };
    Graph gg = Graph(nodes);
    std::vector<std::string> order;
    build_oder(&gg, order);
    std::cout << "order f,e,a,b,d,c is ";
    for(const std::string& s : order) {
        std::cout << s << ",";
    }
    std::cout << std::endl;
    
    //4.8
    std::cout << "first_common_ancestor 5 is " << first_common_ancestor(ba, baaaa, babb)->number << std::endl;
    
    //4.9
    BNode ha = BNode(20, NULL, NULL);
    BNode hb = BNode(60, NULL, NULL);
    BNode hc = BNode(50, &ha, &hb);
    
    std::vector<std::list<int>> bst_sequence = bst_sequences(&hc);
    std::cout << "bst_sequence 50-20-60- | 50-60-20- | is ";
    print_sequences(bst_sequence);
    
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

/*4.3*/
void list_of_depth(BNode* root, int level, std::vector<std::list<BNode*>>& depths) {
    if(root == NULL) return;
    if(depths.size() > level) {
        depths.at(level).push_back(root);
    } else {
        std::list<BNode*> tmp;
        tmp.push_back(root);
        depths.push_back(tmp);
    }
    list_of_depth(root->left, level + 1, depths);
    list_of_depth(root->right, level + 1, depths);
}

/*4.4*/
const bool is_balanced(const BNode* root, int* height) {
    int leftHeight(0);
    int rightHeight(0);
    
    bool left(true), right(true);
    
    if(root == NULL) {
        *height = 0;
        return true;
    }
    
    left = is_balanced(root->left, &leftHeight);
    right = is_balanced(root->right, &rightHeight);
    
    if(leftHeight > rightHeight) {
        *height = leftHeight + 1;
    } else {
        *height = rightHeight + 1;
    }
    
    if(abs(leftHeight - rightHeight) > 1) return false;
    
    return left && right;
}

/*4.5*/
const bool is_bst(const BNode* root, int min, int max) {
    if(root == NULL) return true;
    
    return root->number >= min && root->number < max && is_bst(root->left, min, root->number) && is_bst(root->right, root->number, max);
}

/*4.6*/
const BNode* pick_leftmost(const BNode* node) {
    if(node == NULL) return NULL;
    
    if(node->left != NULL) {
        return pick_leftmost(node->left);
    }
    return node;
}

const BNode* successor(const BNode* node) {
    if(node == NULL) return NULL;
    
    if(node->right != NULL) {
        return pick_leftmost(node->right);
    } else {
        const BNode* tmp = node;
        const BNode* parent = tmp->parent;
        while(parent != NULL && parent->left != tmp) {
            tmp = parent;
            parent = tmp->parent;
        }
        return parent;
    }
    return NULL;
}

/*4.7*/
void dfs(GNode* src, std::vector<std::string>& order) {
    src->is_visited = true;
    for (GNode* n : src->nodes) {
        if(!n->is_visited) {
            dfs(n, order);
        }
    }
    order.push_back(src->name);
}

void build_oder(Graph* g, std::vector<std::string>& order) {
    for (GNode* n : g->nodes) {
        if(!n->is_visited) {
            dfs(n, order);
        }
    }
    std::reverse(order.begin(), order.end());
}

/*4.8*/
const bool contains(const BNode* root, const BNode* n) {
    if(root == NULL || n == NULL) {
        return false;
    }
    if(root == n) {
        return true;
    }
    
    return contains(root->left, n) || contains(root->right, n);
}

const BNode* first_common_ancestor(const BNode* root, const BNode* p, const BNode* q){
    if(root == NULL || root == p || root == q) {
        return root;
    }
    
    bool pLeft = contains(root->left, p);
    bool qLeft = contains(root->left, q);
    if(pLeft != qLeft) {
        // Nodes on different branches
        return root;
    }
    
    if(pLeft) {
        return first_common_ancestor(root->left, p, q);
    }
    return first_common_ancestor(root->right, p, q);
}

/*4.9*/
void weave(std::list<int> a, std::list<int> b, std::list<int> prefix, std::vector<std::list<int>>& r) {
    if(a.size() == 0 || b.size() == 0) {
        std::list<int> result(prefix);
        result.insert(result.end(), a.begin(), a.end());
        result.insert(result.end(), b.begin(), b.end());
        r.push_back(result);
        return;
    }
    
    int head = a.front();
    a.pop_front();
    prefix.push_back(head);
    weave(a, b, prefix, r);
    prefix.pop_back();
    a.push_front(head);
    
    head = b.front();
    b.pop_front();
    prefix.push_back(head);
    weave(a, b, prefix, r);
    prefix.pop_back();
    b.push_front(head);
}

std::vector<std::list<int>> bst_sequences(const BNode* root) {
    std::vector<std::list<int>> result = std::vector<std::list<int>>();
    
    if(root == NULL) {
        result.push_back(std::list<int>());
        return result;
    }
    
    std::list<int> prefix = std::list<int>();
    prefix.push_back(root->number);
    
    std::vector<std::list<int>> left = bst_sequences(root->left);
    std::vector<std::list<int>> right = bst_sequences(root->right);
    
    for(std::list<int> l : left) {
        for(std::list<int> r : right) {
            std::vector<std::list<int>> w = std::vector<std::list<int>>();
            weave(l, r, prefix, w);
            result.insert(result.end(), w.begin(), w.end());
        }
    }
    return result;
}

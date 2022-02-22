#include <iostream>
#include <sstream>
#include <set>

#include "linked_lists.h"

void traverse_and_print(Node* head) {
    Node* tmp = head;
    std::cout << "LinkedList: " << std::endl;
    while(tmp != NULL) {
        std::cout << "e: " << tmp->data << " | " << std::endl;
        tmp = tmp->next;
    }
}

void run_linked_lists() {
    std::cout << "Hello, Linked Lists!" << std::endl;
    Node* a = new Node(4, NULL);
    Node* b = new Node(5, a);
    Node* c = new Node(1, b);
    Node* d = new Node(5, c);
    
    // 2.1
    delete_dups(d);
    traverse_and_print(d);
}

/*2.1*/
void delete_dups(Node* head) {
    std::set<int> elements;
    Node* tmp = head;
    Node* previous = NULL;
    
    while(tmp != NULL) {
        if(elements.find(tmp->data) != elements.end()) {
            // element already exists
            previous->next = tmp->next;
            delete(tmp);
            tmp = previous->next;
        } else{
            elements.insert(tmp->data);
            previous = tmp;
            tmp = tmp->next;
        }
    }
}

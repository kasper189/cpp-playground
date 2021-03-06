#include <iostream>
#include <sstream>
#include <set>
#include <stack>
#include <stdlib.h>

#include "linked_lists.h"
#include "../common/common.h"

void traverse_and_print(Node* head) {
    Node* tmp = head;
    std::cout << "LinkedList: " << std::endl;
    while(tmp != NULL) {
        std::cout << "e: " << tmp->data << " | ";
        tmp = tmp->next;
    }
    std::cout << std::endl;
}

Node* return_last(Node* head) {
    if(head == NULL) return NULL;
    Node* tmp = head;
    
    while(tmp->next != NULL) {
        tmp = tmp->next;
    }
    return tmp;
}

int lenght(Node* a) {
    int size(0);
    Node* tmp = a;
    while(tmp != NULL) {
        size++;
        tmp = tmp->next;
    }
    return size;
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
    
    // 2.2
    Node *e = find_kth_to_last(d, 2);
    std::cout << "find_kth_to_last 1 " << e->data << std::endl;
    
    // 2.3
    std::cout << "delete node true is " << bool_as_text(delete_node(c)) << std::endl;
    traverse_and_print(d); //5-1-4
    
    std::cout << "partition" << std::endl;
    Node* f = new Node(3, NULL);
    Node* g = new Node(5, f);
    Node* h = new Node(8, g);
    Node* i = new Node(5, h);
    Node* j = new Node(10, i);
    Node* k = new Node(2, j);
    Node* l = new Node(1, k);
    Node* m = partition(l, 5);
    traverse_and_print(m);
    
    // 2.5
    Node* aa = new Node(6, NULL);
    Node* ab = new Node(1, aa);
    Node* ac = new Node(7, ab);
    
    Node* ba = new Node(2, NULL);
    Node* bb = new Node(9, ba);
    Node* bc = new Node(5, bb);
    std::cout << "sum list is " << std::endl;
    traverse_and_print(sum_lists(ac, bc));
    
    // 2.6
    Node* ca = new Node(0, NULL);
    Node* cb = new Node(1, ca);
    Node* cc = new Node(99, cb);
    Node* cd = new Node(1, cc);
    Node* ce = new Node(0, cd);
    std::cout << "palindrome true is " << bool_as_text(palindrome(ce)) << std::endl;
    std::cout << "palindrome false is " << bool_as_text(palindrome(cd)) << std::endl;
    
    // 2.7
    Node* da = new Node(5, cc);
    Node* db = new Node(9, da);
    Node* dc = new Node(1, db);
    
    Node* intersection_node = intersection(dc, ce);
    std::cout << "intersection 99 is " << intersection_node->data <<  std::endl;
    
    // 2.8
    Node* loop_node = NULL;
    Node* ea = new Node(99, NULL);
    Node* eb = new Node(2, ea);
    Node* ec = new Node(1, eb);
    ea->next = ec; //create loop
    std::cout << "has_loop true is " << bool_as_text(has_loop(ec, loop_node)) << std::endl;
    std::cout << "has_loop value 1 is " << loop_node->data << std::endl;
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

/*2.2*/
Node* find_kth_to_last(Node* head, const int8_t k)  {
    Node* target = head;
    Node* tmp = head;
    int8_t cnt(k);
    
    while(tmp != NULL && cnt > 0) {
        tmp = tmp->next;
        cnt--;
    }
    
    if(cnt > 0) return NULL;
    
    while(tmp != NULL){
        target = target->next;
        tmp = tmp->next;
    }
    
    return target;
}

/*2.3*/
bool delete_node(Node* previous) {
    if(previous == NULL || previous->next == NULL) {
        return false;
    }
    Node* target = previous->next;
    target->data = target->data;
    target->next = target->next;
    delete target;
    return true;
}

/*2.4*/
Node* partition(Node* head, const int pivot) {
    if(head == NULL) {
        return NULL;
    }
    
    Node* smallers = NULL;
    Node* greaters = NULL;
    Node* equals = NULL;
    Node* visitor = head;
    
    while(visitor != NULL) {
        Node* next = visitor->next;
        visitor->next = NULL;
        
        if(visitor->data < pivot) {
            if(smallers == NULL) {
                smallers = visitor;
            } else {
                smallers->next = visitor;
            }
        } else if(visitor->data > pivot) {
            if(greaters == NULL) {
                greaters = visitor;
            } else {
                greaters->next = visitor;
            }
        } else {
            if(equals == NULL) {
                equals = visitor;
            } else {
                equals->next = visitor;
            }
        }
        visitor = next;
    }
    
    //merging
    Node* last_smaller = return_last(smallers);
    Node* last_equal = return_last(equals);

    if(last_smaller != NULL) {
        if(last_equal != NULL) {
            last_smaller->next = equals;
            last_equal->next = greaters;
        }
        last_equal->next = greaters;
    } else if(last_equal != NULL) {
        smallers = equals;
        last_equal -> next = greaters;
    } else {
        smallers = greaters;
    }
    
    return smallers;
}

/*2.5*/
Node* sum_lists(Node* first, Node* second) {
    //Building the result in correct order
    if(first == NULL) {
        return second;
    }
    if(second == NULL) {
        return first;
    }
    
    Node* a = first;
    Node* b = second;
    Node* result = NULL;
    
    int carry = 0;
    while(a != NULL || b != NULL) {
        int sum(0);
        if(a!= NULL && b != NULL) {
            sum = a->data + b->data + carry;
            a = a->next;
            b = b->next;
        } else if(a == NULL) {
            sum = b->data + carry;
            b = b->next;
        } else {
            sum = a->data + carry;
            a = a->next;
        }
        carry = sum / 10;
        sum = sum % 10;
        Node* node = new Node(sum, result);
        result = node;
    }
    return result;
}

/*2.6*/
const bool palindrome(Node* a) {
    if(a == NULL) return false;
    if(a != NULL && a->next == NULL) return true;
    
    Node* slow = a;
    Node* fast = a;
    
    std::stack<int> stack;
    while(fast != NULL && fast->next != NULL) {
        stack.push(slow->data);
        slow = slow->next;
        fast = fast->next->next;
    }
    
    if(fast != NULL) {
        slow = slow->next;
    }
    
    while(slow != NULL) {
        if(stack.top() != slow->data) {
            return false;
        }
        stack.pop();
        slow = slow->next;
    }
    
    return true;
}

/*2.7*/
Node* intersection(Node* a, Node* b) {
    if(a == NULL || b == NULL) return NULL;
    
    int size_a = lenght(a);
    int size_b = lenght(b);
    
    Node* longer =  NULL;
    Node* shorter = NULL;
    
    if(size_a > size_b) {
        longer = a;
        shorter = b;
    } else {
        longer = b;
        shorter = a;
    }
    
    int diff(abs(size_b - size_a));
    
    while(diff > 0) {
        longer = longer ->next;
        --diff;
    }
    
    while(longer != NULL && shorter != NULL) {
        if(longer == shorter) {
            return longer;
        }
        longer = longer->next;
        shorter = shorter->next;
    }
    
    return NULL;
}

/*2.8*/
const bool has_loop(Node* head, Node*& begin) {
    if(head == NULL) {
        begin = NULL;
        return false;
    }
    
    std::set<Node*> nodes;
    Node* visitor = head;
    while(visitor != NULL) {
        if(nodes.find(visitor) != nodes.end()) {
            begin = visitor;
            return true;
        }
        nodes.insert(visitor);
        visitor = visitor->next;
    }
    return false;
}

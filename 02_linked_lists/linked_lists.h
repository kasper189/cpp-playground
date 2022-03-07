#ifndef linked_lists_h
#define linked_lists_h

class Node {
    public:
        int data;
        Node* next;
        
    Node(int data, Node* next) : data(data), next(next) {}
    
};

void run_linked_lists();

//Exercises
void delete_dups(Node* head);
Node* find_kth_to_last(Node* head, const int8_t k);
bool delete_node(Node* previous);
Node* partition(Node* head, const int pivot);
Node* sum_lists(Node* first, Node* second);
const bool palindrome(Node* a);

#endif /* linked_lists_h */

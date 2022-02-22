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


#endif /* linked_lists_h */

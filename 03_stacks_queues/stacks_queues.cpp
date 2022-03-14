#include <iostream>
#include <stdio.h>

#include "stacks_queues.h"
#include "../common/common.h"

void traverse_and_print(std::stack<int> s) {
    std::cout << "Stack: " << std::endl;
    while(!s.empty()) {
        std::cout << "e: " << s.top() << " | ";
        s.pop();
    }
    std::cout << std::endl;
}

void run_stacks_queues() {
    std::cout << "Hello, Stacks & Queues!" << std::endl;
    
    // 3.5
    std::stack<int> a;
    a.push(1);
    a.push(9);
    a.push(3);
    a.push(5);
    a.push(7);
    sort_stack(a);
    std::cout << "sorted stack 1|3|5|7|9 is " << std::endl;
    traverse_and_print(a);
}

/*3.5*/
void sort_stack(std::stack<int>& s) {
    std::stack<int> buffer;
    //Assumption: sorting in ascending order
    while(!s.empty()) {
        int target = s.top();
        s.pop();
        while(!buffer.empty() && buffer.top() > target) {
            s.push(buffer.top());
            buffer.pop();
        }
        buffer.push(target);
    }
    while(!buffer.empty()) {
        s.push(buffer.top());
        buffer.pop();
    }
    return;
}


#include "ADT.hpp"

class Solution {
public:
    Node* flatten(Node* head) {
        if(!head) return nullptr;
        auto t = head;
        while(t){
            auto ne = t->next;
            if(t->child){
                t->next = flatten(t->child);
                t->next->prev = t;
                t->child = nullptr;
                while(t->next) t = t->next;
            }
            t->next = ne;
            if(ne) ne->prev = t;
            t = ne;
        }
        return head;
    }   
};
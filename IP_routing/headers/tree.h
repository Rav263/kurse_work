#include "table_io.h"

#ifndef TREE
#define TREE
class Node {
public:
    int mask;
    IP net_ip;
    uint32_t current_bit;
    Node *left;
    Node *right;
    int32_t depth;

    Node(int mask, IP net_ip, Node *left, Node *right):
        mask(mask), net_ip(net_ip), left(left), right(right) {
        
        current_bit = 0;
    }

    Node(

    Node(uint32_t current_bit, Node *left, Node *right): 
        current_bit(current_bit), left(left), right(right) {
        net_ip = 0;
        mask   = 0;
    }

    Node() {
        mask  = 0;
        current_bit = 0;
        net_ip = 0;
        left  = nullptr;
        right = nullptr;
    }
};


#endif

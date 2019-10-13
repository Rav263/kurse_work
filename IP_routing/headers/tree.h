#include "table_io.h"

#ifndef TREE
#define TREE
class Node {
public:
    int mask;
    IP net_ip;
    Node *left;
    Node *right;
    
    Node(int mask, IP net_ip, Node *left, Node *right):
        mask(mask), net_ip(net_ip), left(left), right(right) {}
    
    Node() {
        mask  = 0;
        net_ip = 0;
        left  = nullptr;
        right = nullptr;
    }
};


#endif

#include "table_io.h"

#ifndef TREE
#define TREE
class Node {
public:
    IP mask;
    int net_ip;
    Node *left;
    Node *right;
    
    Node(int mask, IP net_ip, Node *left, Node *right):
        mask(mask), left(left), right(right), net_ip(net_ip) {}
    
    Node() {
        mask  = 0;
        net_ip = 0;
        left  = nullptr;
        right = nullptr;
    }
};


#endif

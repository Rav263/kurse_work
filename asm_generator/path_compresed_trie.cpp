#include <map>
#include <iostream>
#include <vector>
#include <set>


class Node {
public:
    Node *left;
    Node *right;
    
    uint64_t mask;
    uint64_t ip;

    Node(Node* left, Node* right, uint64_t mask, uint64_t ip) : left(left), right(right), mask(mask), ip(ip) {}

};



Node *insert_node(Node **now_node, 

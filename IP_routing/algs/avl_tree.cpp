#include <iostream>
#include <map>
#include <vector>
#include <bitset>


#include "../headers/table_io.h"
#include "../headers/tree.h"

//#define DEBUG

bool prefix_compare(Net_IP net_ip_1, Net_IP net_ip_2) {
    if (net_ip_1.second == net_ip_2.second) {
#ifdef DEBUG
        std::cout << intip_to_string(net_ip_1) << "(" << net_ip_1.first << ") < ";
        std::cout << intip_to_string(net_ip_2) << "(" << net_ip_2.first << ") = ";
#endif
        return net_ip_1.first < net_ip_2.first;
    }
    if (net_ip_1.second < net_ip_2.second) { 
#ifdef DEBUG
        std::cout << intip_to_string(net_ip_1) << "(" << (net_ip_1.first >> (32 - net_ip_1.second))<< ") < ";
        std::cout << intip_to_string(net_ip_2) << "(" << (net_ip_2.first >> (32 - net_ip_1.second))<< ") = "; 
#endif
        return (net_ip_1.first >> (32 - net_ip_1.second)) < (net_ip_2.first >> (32 - net_ip_1.second));
    }
#ifdef DEBUG
    std::cout << intip_to_string(net_ip_1) << "(" << (net_ip_1.first >> (32 - net_ip_2.second))<< ") < ";
    std::cout << intip_to_string(net_ip_2) << "(" << (net_ip_2.first >> (32 - net_ip_2.second))<< ") = "; 
#endif
    return (net_ip_1.first >> (32 - net_ip_2.second)) < (net_ip_2.first >> (32 - net_ip_2.second));
}


Node *right_rotate(Node *now_node) {
    Node *right_left_node = now_node->left->right;
    Node *left_node       = now_node->left;
    
    left_node->right = now_node;
    now_node->left   = right_left_node;

    now_node->depth = std::max(now_node->left->depth, now_node->right->depth) + 1;
    left_node->depth = std::max(left_node->left->depth, left_node->right->depth) + 1;

    return left_node;
}


Node *left_rotate(Node *now_node) {
    Node *right_node = now_node->right;
    Node *right_left_node = now_node->right->left;

    right_node->left = now_node;
    now_node->right = right_left_node;

    now_node->depth = std::max(now_node->left->depth, now_node->right->depth) + 1;
    right_node->depth = std::max(right_node->left->depth, right_node->right->depth) + 1;

    return right_node;
}


Node *big_right_rotate(Node *now_node) {
    now_node->right = right_rotate(now_node->right);
    
    return left_rotate(now_node);
}


Node *big_left_rotate(Node *now_node) {
    now_node->left = left_rotate(now_node->left);
    
    return right_rotate(now_node);
}

Net_IP get_net_ip(Node *now_node) {
    return {now_node->net_ip, now_node->mask};
}

Node *rotate_node(Node *now_node, Net_IP net_ip) {
    auto balance = now_node->left->depth - now_node->right->depth;

    if (balance > 1  and prefix_compare(net_ip, get_net_ip(now_node->left)))
        return left_rotate(now_node);
    if (balance < -1 and prefix_compare(get_net_ip(now_node->right), net_ip))
        return right_rotate(now_node);
    if (balance > 1  and prefix_compare(get_net_ip(now_node->left), net_ip))
        return big_left_rotate(now_node);
    if (balance < -1 and prefix_compare(net_ip, get_net_ip(now_node->right)))
        return big_right_rotate(now_node);

    return now_node;
}


static Node* add_node(Node *root, Net_IP net_ip) {
    if (root == nullptr)
        return new Node(net_ip.second, net_ip.first, nullptr, nullptr);
    if (prefix_compare(net_ip, get_net_ip(root)))
        root->left = add_node(root->left, net_ip);
    else 
        root->right = add_node(root->right, net_ip);

    root->depth = std::max(root->left->depth, root->right->depth) + 1;

    return root;
}


Node *build_avl_tree(Table &table) {
    Node *root = nullptr;

    for (auto now_entry : table) {
        root = add_node(root, now_entry.first);
    }

    return root;
}

Net_IP find_node_avl(Node *now_node, IP sr_ip, int32_t depht) {
    std::string str_an_ip;
    std::cin >> str_an_ip;
    IP an_ip = strip_to_int(str_an_ip);

    int32_t mask_1, mask_2;
    std::cin >> mask_1 >> mask_2;

    std::cout << prefix_compare({sr_ip, mask_1}, {an_ip, mask_2}) << std::endl;

    return {0, 0};
}

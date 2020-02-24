#include <iostream>
#include <map>
#include <vector>
#include <bitset>


#include "../headers/table_io.h"
#include "../headers/tree.h"

bool prefix_compare(Net_IP net_ip_1, Net_IP net_ip_2) {
    if (net_ip_1.second == net_ip_2.second) {
        std::cout << intip_to_string(net_ip_1) << "(" << net_ip_1.first << ") < ";
        std::cout << intip_to_string(net_ip_2) << "(" << net_ip_2.first << ") = ";
        return net_ip_1.first < net_ip_2.first;
    }
    if (net_ip_1.second < net_ip_2.second) { 
        std::cout << intip_to_string(net_ip_1) << "(" << (net_ip_1.first >> (32 - net_ip_1.second))<< ") < ";
        std::cout << intip_to_string(net_ip_2) << "(" << (net_ip_2.first >> (32 - net_ip_1.second))<< ") = "; 
        return (net_ip_1.first >> (32 - net_ip_1.second)) < (net_ip_2.first >> (32 - net_ip_1.second));
    }
    
    std::cout << intip_to_string(net_ip_1) << "(" << (net_ip_1.first >> (32 - net_ip_2.second))<< ") < ";
    std::cout << intip_to_string(net_ip_2) << "(" << (net_ip_2.first >> (32 - net_ip_2.second))<< ") = "; 
    return (net_ip_1.first >> (32 - net_ip_2.second)) < (net_ip_2.first >> (32 - net_ip_2.second));
}

static void add_node(Node *root, Net_IP net_ip) {
    std::bitset<32> ip_set(net_ip.first);
    
    Node **now_node = &root;

}

Node *build_avl_tree(Table &table) {
    Node *root = new Node();

    for (auto now_entry : table) {
        std::cout << intip_to_string(now_entry);
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

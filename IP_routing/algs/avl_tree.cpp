#include <iostream>
#include <map>
#include <vector>
#include <bitset>


#include "../headers/table_io.h"
#include "../headers/tree.h"

bool prefix_compare(Net_IP net_ip_1, Net_IP net_ip_2) {
    if (net_ip_1.second == net_ip_2.second) return net_ip_1.first < net_ip_2.first;
    if (net_ip_1.second < net_ip_2.second) 
        return (net_ip_1.first >> (32 - net_ip_1.second)) < (net_ip_2.first >> (32 - net_ip_1.second));
    return (net_ip_1.first >> (32 - net_ip_2.second)) < (net_ip_2.first >> (32 - net_ip_2.second));
}

static void add_node(Node *root, Net_IP net_ip) {
    std::bitset<32> ip_set(net_ip.first);
    
    Node **now_node = &root;

}

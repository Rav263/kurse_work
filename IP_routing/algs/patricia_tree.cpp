#include <iostream>
#include <map>
#include <bitset>

#include "../headers/table_io.h"
#include "../headers/tree.h"

static void add_node(Node **now_node, Net_IP net_ip, uint32_t last_gone) {
    if (*now_node == nullptr) {
        *now_node = new Node(net_ip.second, net_ip.first, nullptr, nullptr);
        (*now_node)->current_bit = 32 - net_ip.second;
        return;
    }

    auto tmp_bit = (*now_node)->current_bit;
    auto ip_now  = (*now_node)->net_ip;
    
    std::bitset<32> ip_set_sr(net_ip.first);
    std::bitset<32> ip_set_now(ip_now);

    auto min_bit = (int)tmp_bit > net_ip.second ? tmp_bit : net_ip.second;

    for (uint32_t i = last_gone; i >= min_bit; i--) {
        if (ip_set_sr[i] != ip_set_now[i]) {
            auto tmp_ptr = *now_node;

            if (ip_set_now[i]) {
                *now_node = new Node(net_ip.second, net_ip.first, tmp_ptr, 
                            new Node(net_ip.second, net_ip.first, nullptr, nullptr));

                (*now_node)->current_bit = i;
                return;
            }
        }
    }

    if (ip_set_sr[tmp_bit])
        add_node(&(*now_node)->left,  net_ip, tmp_bit);
    else
        add_node(&(*now_node)->right, net_ip, tmp_bit);
}


Net_IP find_node_patricia(Node *now_node, IP sr_ip, uint32_t deph) {
    if (now_node == nullptr) return {0, 0};

    if (now_node->mask != 0 and now_node->net_ip != 0) {
        auto tmp = find_node_patricia((sr_ip & (1 << (31 - deph))) ? now_node->left : now_node->right, sr_ip, deph + 1);

        if (tmp.second > now_node->mask) return tmp;
        else return {now_node->net_ip, now_node->mask};
    } else {
        return find_node_patricia((sr_ip & (1 << (31 - deph))) ? now_node->left : now_node->right, sr_ip, deph + 1);
    }
}


// recursive tree printing
static void print_node(Node *start, int height) {
    if (start == nullptr) return;
    for(int i = 0; i < height; i++) {
        std::cout << "::";
    }
    std::cout << " " << intip_to_string({{start->net_ip, start->mask},0});
    print_node(start->left,  height + 1);
    print_node(start->right, height + 1);
}


// Adding all entries from table into tree
Node *build_patricia_tree(Table &table) {
    Node *root = new Node();
    root->current_bit = 31;

    for (auto now_entry : table) {
        add_node(&root, now_entry.first, root->current_bit);
    }
    
    print_node(root, 0);

    return root;
}

#include <iostream>
#include <map>
#include <vector>
#include <bitset>


#include "table_io.h"

class Node {
public:
    IP mask;
    int net_ip;
    Node *left;
    Node *right;
    
    Node(int mask, IP net_ip, Node *left, Node *right): mask(mask), left(left), right(right), net_ip(net_ip) {}
    Node() {
        mask  = 0;
        net_ip = 0;
        left  = nullptr;
        right = nullptr;
    }
};

void add_node(Node *root, Net_IP net_ip) {
    std::bitset<32> ip_set(net_ip.first);
    Node **now_node = &root;

    int ind;
    for (ind = 31; ind >= 31 - net_ip.second and *now_node != nullptr; ind--) {
        now_node = ip_set[ind] ? &(*now_node)->left : &(*now_node)->right;
    }

    for (;ind >= 31 - net_ip.second; ind--) {
        *now_node = new Node();
        now_node = ip_set[ind] ? &(*now_node)->left : &(*now_node)->right;
    }

    if (*now_node == nullptr) {
        *now_node = new Node(net_ip.second, net_ip.first, nullptr, nullptr);
    } else {
        (*now_node)->mask   = net_ip.second;
        (*now_node)->net_ip = net_ip.first;
    }
}

Node *build_radix_tree(Table &table) {
   Node *root = new Node();

    for (auto now_entry : table) {
        std::cout << intip_to_string(now_entry);
        add_node(root, now_entry.first);
    }

    return root;
}

void print_node(Node *start, int height) {
    if (start == nullptr) return;
    for(int i = 0; i < height; i++) {
        std::cout << "::";
    }
    std::cout << " " << intip_to_string({{start->net_ip, start->mask},0});
    print_node(start->left,  height + 1);
    print_node(start->right, height + 1);
}

Net_IP find_node(Node *now_node, IP sr_ip, uint32_t deph) {
    if (now_node == nullptr) return {0, 0};

    if (now_node->mask != 0 and now_node->net_ip != 0) {
        auto tmp = find_node((sr_ip & (1 << 31 - deph)) ? now_node->left : now_node->right, sr_ip, deph + 1);

        if (tmp.second > now_node->mask) return tmp;
        else return {now_node->net_ip, now_node->mask};
    } else {
        return find_node((sr_ip & (1 << 31 - deph)) ? now_node->left : now_node->right, sr_ip, deph + 1);
    }
}

int main() {
    Table table;
    std::string file_name;
    
    std::cin >> file_name;
    read_table(file_name, table);
    Node *root = build_radix_tree(table);

    std::string sr_ip;

    while (std::cin >> sr_ip) {
        auto tmp = find_node(root, strip_to_int(sr_ip), 0);
        std::cout << tmp.first << " " << tmp.second << std::endl;
        std::cout << intip_to_string({tmp, table[tmp]});
    }
    //    print_node(root, 0);
}

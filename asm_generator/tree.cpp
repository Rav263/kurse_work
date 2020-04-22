#include <iostream>
#include <map>
#include <vector>
#include <bitset>
#include <set>
#include <fstream>

using Mask      = std::pair<uint64_t, uint64_t>;
using Table_mac = std::map<uint64_t, std::set<uint64_t>>; // from, to
using Defs      = std::vector<std::pair<std::string, std::string>>; // name, value
using ModDefs   = std::map<std::string, uint64_t>; // name, value;
using Table_ip  = std::map<Mask, std::set<uint64_t>>;

class Node {
public:
    Node *left;
    Node *right;
    uint64_t port_num;

    Node(Node *left, Node *right, uint64_t port_num = 63): left(left), right(right), port_num(port_num) {}
};

uint64_t strip_to_int(std::string& ip) {
    uint64_t num_ip = 0;
    uint64_t now_itr = 0;

    for (auto chr : ip) {
        if (chr == '.') {
            num_ip += now_itr;
            num_ip <<= 8;
            now_itr = 0;
        } else {
            now_itr *= 10;
            now_itr += chr - '0';
        }
    }
    num_ip += now_itr;

    return num_ip;
}

void insert_node(Node *now, const std::bitset<32> &ip, uint64_t current_bit, uint64_t deph, uint64_t port) {
    if (deph == 0) {
        now->port_num = port;
        return;
    }

    if (ip[current_bit]) {
        if (now->right == nullptr) {
            now->right = new Node(nullptr, nullptr);
        }

        insert_node(now->right, ip, current_bit - 1, deph - 1, port);
    } else {
        if (now->left == nullptr) {
            now->left = new Node(nullptr, nullptr);
        }

        insert_node(now->left, ip, current_bit - 1, deph - 1, port);
    }
}


Node* build_tree(Table_ip &table) {
    Node *root = new Node(nullptr, nullptr);
    
    for (auto now_entrie : table) {
        for (auto now : now_entrie.second) {
            insert_node(root, std::bitset<32>(now_entrie.first.first),
                    31, now_entrie.first.second, now);
        }
    }

    return root;
}

void print_tree(Node *now, uint64_t deph) {
    if (now == nullptr) return;

    for (int i = 0; i < deph; i++) {
        std::cout << "::";
    }
    
    std::cout << " " << now->port_num << std::endl;

    print_tree(now->left,  deph + 1);
    print_tree(now->right, deph + 1);
}


void gen_asm(Node *root, uint64_t deph, bool left, std::ofstream &file) {
    file << "root_" << deph << (left ? "_0:" : "_1:") << std::endl;
    
    if (root == nullptr) {
        file << "j finish" << std::endl;
        return;
    }

    if (root->port_num != 63) {
        file << "setxmask (1 << " << std::dec << root->port_num << ")" << std::endl;
    }
    
    file << "cpmj " << "root_" << deph + 1 << "_1, " << "0x1, 1" << std::endl;
    file << "j root_" << deph + 1 << "_0" << std::endl;

    gen_asm(root->right, deph + 1, false, file);
    gen_asm(root->left, deph + 1, true, file);
}

std::ofstream open_out_file() {
    std::string name;
    std::ofstream file;
    std::cout << "Enter file name: " <<  std::endl;

    while (std::cin >> name) {
        file.open(name);
        if (file.is_open()) break;

        std::cerr << "ERROR:: Can't open file, try again" << std::endl;
    }

    return file;
}

int main() {
    Table_ip table;
    uint64_t mask, port;
    std::string ip, tmp_1, tmp_2;
    int index = 0;
    
    auto file = open_out_file();
    
    while (std::cin >> ip >> tmp_1 >> tmp_2 >>  mask >> tmp_1 >> tmp_2) {
        if (index > 100) break;
        std::cout << ip << " " << mask << std::endl;

        table[{strip_to_int(ip), mask}].insert(index);
        index += 1;
    }

    Node *root = build_tree(table);


    gen_asm(root, 0, true, file);

    file << "finish:" << std::endl;
    file.close();
}

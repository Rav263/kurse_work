#include <iostream>

#include "./headers/table_io.h"
#include "./headers/algorithms.h"

#define DEBUG

void linary(Table &table) {
    std::string ip;

    while (std::cin >> ip) {
        auto founded_entrie = linary_search(table, strip_to_int(ip));

        if (founded_entrie.first.second == -1) 
            std::cout << " ===> default" << std::endl;
        else 
            std::cout << intip_to_string(founded_entrie);
    }
}

void radix(Table &table) {
    std::string file_name;
    
    std::cin >> file_name;
    read_table(file_name, table);
    Node *root = build_radix_tree(table);

    std::string sr_ip;

    while (std::cin >> sr_ip) {
        auto tmp = find_node(root, strip_to_int(sr_ip), 0);
        if (tmp.second == 0) 
            std::cout << " ===> default" << std::endl;
        else
            std::cout << intip_to_string({tmp, table[tmp]});
    }
}

void particia(Table &table) {
    std::cout << "Comming soon" << std::endl;
}
void huffman(Table &table) {
    std::cout << "Comming soon" << std::endl;
}
void alfabetic(Table &table) {
    std::cout << "Comming soon" << std::endl;
}



int main() {
    std::string file_name;
    Table table;

    std::cerr << "Enter table file name: ";
    std::cin >> file_name;
    read_table(file_name, table);
#ifdef DEBUG
    print_table(table);
#endif
    std::cerr << "1 -- linary  search" << std::endl
              << "2 -- radix     tree" << std::endl
              << "3 -- patricia  tree" << std::endl
              << "4 -- huffman   tree" << std::endl
              << "5 -- alfabetic tree" << std::endl;
    int alg;
    std::cin >> alg;

    if      (alg == 1) linary(table);
    else if (alg == 2) radix(table);
    else if (alg == 3) particia(table);
    else if (alg == 4) huffman(table);
    else if (alg == 5) alfabetic(table);
    else {
        std::cerr << "Not correct num" << std::endl;
    }
}

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <bitset>
#include "table_io.h"


//#define DEBUG

std::pair<Net_IP, int> linary_search(Table &table, IP sr_ip) {
    std::pair<Net_IP, int> max_entr = {{0, -1}, 0};

    for (auto now_entrie : table) {
        IP mask = now_entrie.first.second;
        IP ip   = now_entrie.first.first;

        mask = (1 << mask) - 1;
        mask <<= 32 - now_entrie.first.second;
#ifdef DEBUG 
        std::cout << "mask:  " << std::bitset<32>(mask)  << " " << mask  << std::endl 
                  << "sr ip: " << std::bitset<32>(sr_ip) << " " << sr_ip << std::endl
                  << "ip:    " << std::bitset<32>(ip)    << " " << ip    << std::endl
                  << "check: " << std::bitset<32>((sr_ip & mask) ^ (ip & mask)) << " " 
                  <<                   ((sr_ip & mask) ^ (ip & mask)) << std::endl;
#endif
        if (((sr_ip & mask) ^ (ip & mask)) == 0) {
            if (max_entr.first.second < now_entrie.first.second) {
                max_entr = now_entrie;
            }
        }
    }

    return max_entr;
}

int main() {
    std::string file_name;
    Table table;

    std::cin >> file_name;
    read_table(file_name, table);
    print_table(table);

    std::string ip;

    while (std::cin >> ip) {
        auto founded_entrie = linary_search(table, strip_to_int(ip));

        if (founded_entrie.first.second == -1) 
            std::cout << " ===> default" << std::endl;
        else 
            std::cout << intip_to_string(founded_entrie);
    }
}

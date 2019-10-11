#include <map>
#include <iostream>
#include <string>
#include <fstream>

void read_table(std::string &file_name, std::map<std::pair<uint32_t, int>, int> &table) {
    std::ifstream file;
    file.open(file_name);

    uint32_t ip, mask, port;
    
    while (file >> ip >> mask >> port) {
        table[{ip, mask}] = port;
    }
}

void print_table(std::map<std::pair<uint32_t, int>, int> &table) {
    for (auto now_entry : table) {
        uint32_t ip   = now_entry.first.first;
        uint32_t mask = now_entry.first.second;
        uint32_t port = now_entry.second;

        std::cout << (ip & 255) << ".";
        ip >>= 8;
        std::cout << (ip & 255) << ".";
        ip >>= 8;
        std::cout << (ip & 255) << ".";
        ip >>= 8;
        std::cout << (ip & 255) << "\\" << mask << " ===> " << port << std::endl;
    }
}

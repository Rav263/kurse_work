#include <map>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "../headers/table_io.h"


uint32_t strip_to_int(std::string& ip) {
    uint32_t num_ip = 0;
    uint32_t now_itr = 0;

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


std::string intip_to_string(std::pair<Net_IP, int> now_entry) {
    uint32_t ip   = now_entry.first.first;
    uint32_t mask = now_entry.first.second;
    uint32_t port = now_entry.second;

    std::stringstream str_in;

    str_in << ((ip & (255 << 24)) >> 24) << ".";
    str_in << ((ip & (255 << 16)) >> 16) << ".";
    str_in << ((ip & (255 << 8 )) >> 8)  << ".";
    str_in << (ip & 255) << "\\" << mask << " ===> " << port << std::endl;
    
    return str_in.str();
}

void read_table(std::string &file_name, Table &table) {
    std::ifstream file;
    file.open(file_name);
    if (not file.is_open()) {
        std::cerr << "FILE NOT OPEN" << std::endl;
        exit(1);
    }

    uint32_t ip, mask, port;
    
    while (file >> ip >> mask >> port) {
        table[{ip, mask}] = port;
    }
}

void print_table(Table &table) {
    for (auto now_entry : table) {
        std::cout << intip_to_string(now_entry);
    }
}

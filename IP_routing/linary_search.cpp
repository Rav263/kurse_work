#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "table_io.h"

uint32_t strip_to_int(std::string& ip) {
    uint32_t num_ip = 0;
    uint32_t now_itr = 0;

    for (auto chr : ip) {
        if (chr == '.') {
            num_ip += now_itr;
            num_ip <<= 8;
        } else {
            now_itr *= 10;
            now_itr += chr - '0';
        }
    }

    num_ip += now_itr;

    return num_ip;
}



int main() {
    std::string file_name;
    std::map<std::pair<uint32_t, int>, int> table;

    std::cin >> file_name;

    read_table(file_name, table);


    std::string ip;

    while (std::cin >> ip) {
        std::cout << strip_to_int(ip) << std::endl;
    }
}

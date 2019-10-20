#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <set>
#include <fstream>
/*
 * If we have rule to go table it must look like 0x1000 & table_num
 * If we have rule to go port it must look like 0x2000 & port_num
 */


using Table = std::map<uint64_t, std::set<uint64_t>>; // from, to
using Defs  = std::map<std::string, std::string>; // name, value

void parse_string_def(Defs &definitions, Defs &default_defs, std::string &value) {
    std::string now_word = "";

    std::vector<std::string> words;

    for (auto now_char : value) {
        if (now_char == '(') {
            now_word;
        }
    }
}


void load_default_definitions(Defs &definitions) {
    std::ifstream in_file;
    in_file.open("npu_de_defines.h");

    if (not in_file.is_open()) {
        std::cerr << "ERROR: no npu_de_defines.h file!!" << std::endl;
        return;
    }

    std::string now_string;

    while (in_file >> now_string) {
        if (now_string.compare("#define")) continue;
        std::string name, value;

        in_file >> name >> value;

        definitions[name] = value;
    }
}

void print_defs(Defs &definitions) {
    for (auto now_def : definitions) {
        std::cout << now_def.first << " " << now_def.second << std::endl;
    }
}

void read_table_args(std::map<std::string, uint64_t> &args) {
    std::cout << "Reading args" << std::endl;
    std::string arg_name;

    while (std::cin >> arg_name) {
        if (not arg_name.compare("size")) {
            uint64_t size;
            std::cin >> size;
            args["size"] = size;

        } else if (not arg_name.compare("ipv4")) {
            args["size"] = 32; 
       
        } else if (not arg_name.compare("ipv6")) {
            args["size"] = 128;

        } else if (not arg_name.compare("mac")) {
            args["size"] = 48;

        } else if (not arg_name.compare("end")) {
            break;
        }
    }
}


std::string read_table(Table &table, const std::string &str, Defs &definitions, std::map<std::string, uint64_t> &args) {
    std::cout << "---- TABLE ----" << std::endl;
    std::cout << "Searched value: " << std::endl;
    std::string name;

    while (std::cin >> name) {
        if (definitions.count(name)) break;
        std::cout << "Invalid definition" << std::endl;
    }

    read_table_args(args);

    std::cout << "Reading table: " << str << std::endl;
    uint64_t from, to;

    while (std::cin >> from) {
        if (from == (uint64_t) -1) break;
        std::cin >> to;
        table[from].insert(to);
    }

    return name;
}



void print_header_l2(std::ofstream &file, Defs &definitions) {
    file << "// THIS IS AUTO GENERATED CODE" << std::endl;
    file << "#include \"npu_de_defines.h\"" << std::endl;
    file << std::endl;
    file << "// HEADER STRUCTURE DEFINITIONS" << std::endl;

    for (auto now_def : definitions) {
        file << "#define " << now_def.first << " " << now_def.second << std::endl;
    } 
    file << std::endl;
}


void read_header_structure(Defs &definitions) {
    std::cout << "Reading header structure (numbers in dec form): " << std::endl;
    
    std::string def, value;

    while (std::cin >> def) {
        if (not def.compare("end")) break;
        std::cin >> value;
        definitions[def] = value;
    }
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


void parse_table(Table &table, std::ofstream &file, std::string &def, 
        std::map<std::string, uint64_t> &args, Defs &definitions, const std::string &name) {
    file << std::endl << "// ------ Table: " << name << " parsing" << std::endl;
    auto size = args["size"];

    auto alignment = size - std::stoull(definitions[def]) & size;

    if (alignment != size) {
        file << "loadbe " << def << ", " << alignment << std::endl;
        file << "rol " << size - alignment << std::endl;
        file << "orbe (" << def << " + " << (alignment / 8) << "), " << size - alignment << std::endl;
    } else {
        file << "loadbe " << def << ", " << size << std::endl;
    }


}


int main() {
    Table table_1, table_2;
    Defs definitions;
    Defs default_defs;
    std::map<std::string, uint64_t> args_1, args_2;

    load_default_definitions(default_defs);
    read_header_structure(definitions);
    print_defs(definitions);
    
    auto search_1 = read_table(table_1, "table_1", definitions, args_1);
    auto search_2 = read_table(table_2, "table_2", definitions, args_2);
   
    auto out_file = open_out_file();
    print_header_l2(out_file, definitions);

    parse_table(table_1, out_file, search_1, args_1, definitions, "table_1");
    parse_table(table_2, out_file, search_2, args_2, definitions, "table_2");
}

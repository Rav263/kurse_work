#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <set>
#include <fstream>

#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

/*
 * If we have rule to go table it must look like 0x1000 & table_num
 * If we have rule to go port it must look like 0x2000 & port_num
 */


using Table   = std::map<uint64_t, std::set<uint64_t>>; // from, to
using Defs    = std::vector<std::pair<std::string, std::string>>; // name, value
using ModDefs = std::map<std::string, uint64_t>; // name, value;


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

        definitions.push_back({name, value});
    }
}

void print_defs(Defs &definitions) {
    for (auto now_def : definitions) {
        std::cout << now_def.first << " " << now_def.second << std::endl;
    }
}

void print_defs(ModDefs &definitions) {
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


std::string read_table(Table &table, const std::string &str, ModDefs &definitions, std::map<std::string, uint64_t> &args) {
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
        std::cin >> std::hex >> to;
        table[from].insert(to);
    }

    return name;
}



void print_header_l2(std::ofstream &file, Defs &definitions, ModDefs &mod_definitions) {
    file << "// THIS IS AUTO GENERATED CODE" << std::endl;
    file << "#include \"npu_de_defines.h\"" << std::endl;
    file << std::endl;
    file << "// HEADER STRUCTURE DEFINITIONS" << std::endl;

    for (auto now_def : definitions) {
        file << "#define " << now_def.first << " " << now_def.second 
             << " // 0x" << std::hex << mod_definitions[now_def.first] << std::endl;
    } 
    file << std::endl;
}


void read_header_structure(Defs &definitions) {
    std::cout << "Reading header structure (numbers in dec form): " << std::endl;
    
    std::string def, value;

    while (std::cin >> def) {
        if (not def.compare("end")) break;
        std::cin >> value;
        definitions.push_back({def, value});
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


/* We realy need refactor table name system!!
 * Now table name in std::string must be "table_{index}"
 */

void linear_search(Table &table, std::ofstream &file, const std::string &name, uint64_t msk) {
    int index = 0;

    for (auto now_entrie : table) {
        file << "cmpj " << name << "_" << std::dec << index << ", 0x" 
             << std::hex << now_entrie.first << ", " << std::dec << msk << std::endl;
        index += 1;
    }

    file << "j finish" << std::endl << std::endl;

    index = 0;

    for (auto now_entrie : table) {
        file << name << "_" << std::dec << index << ":" << std::endl;

        uint64_t next_table_index = 0;

        for (auto now_rule : now_entrie.second) {
            if (now_rule & 0x1000) {
                next_table_index = now_rule ^ 0x1000;
            } else if (now_rule & 0x2000) {
                file << "setmask " << std::hex << (now_rule ^ 0x2000) << std::endl;
            }
        }

        if (next_table_index) { 
            file << "j table_" << std::dec << next_table_index << std::endl;
        } else {
            file << "j finish" << std::endl;
        }
        index += 1;
        file << std::endl;
    }

}


void parse_table(Table &table, std::ofstream &file, std::string &def, 
        std::map<std::string, uint64_t> &args, ModDefs &definitions, const std::string &name) {
    file << std::endl << "// ------ Table: " << name << " parsing" << std::endl;
    auto size = args["size"];

    auto alignment = size - definitions[def] & size;

    file << name << ":" << std::endl << std::endl;
    
    if (alignment != size) {
        file << "loadbe " << def << ", " << alignment << std::endl;
        file << "rol " << size - alignment << std::endl;
        file << "orbe (" << def << " + " << (alignment / 8) << "), " << size - alignment << std::endl;
    } else {
        file << "loadbe " << def << ", " << size << std::endl;
    }
    file << std::endl;

    linear_search(table, file, name, size);
}

void modify_definitions(Defs &definitions, Defs &default_defs, ModDefs &mody_defs) {
    std::ofstream out_file;
    out_file.open(".definitions.tmp");

    if (not out_file.is_open()) {
        std::cerr << "FATAL ERROR:: Can't open tmp file" << std::endl;
        exit(1);
    }

    for (auto now_def : default_defs) {
        out_file << "#define " << now_def.first << " " << now_def.second << std::endl;
    }

    for (auto now_def : definitions) {
        out_file << "#define " << now_def.first << " " << now_def.second << std::endl;
    }

    out_file << "end" << std::endl;
    out_file.close();

    if (fork() == 0) {
        execlp("/bin/sh", "/bin/sh", "-c", "python parser.py < .definitions.tmp > .mod_defs.tmp", NULL);
    }
    wait(0);


    std::ifstream in_file;
    in_file.open(".mod_defs.tmp");

    if (not in_file.is_open()) {
        std::cerr << "FATAL ERROR:: Can't open tmp file" << std::endl;
        exit(1);
    }

    std::string now_name;
    uint64_t value;

    while (in_file >> now_name >> value) {
        mody_defs[now_name] = value;
    }

    if (fork() == 0) execlp("rm", "rm", ".definitions.tmp", ".mod_defs.tmp");

    wait(0);
    wait(0);
}

void print_table(Table &table, const std::string &name) {
    std::cout << "PRINTING TABLE: " << name << std::endl;

    for (auto now_entrie : table) {
        std::cout << (now_entrie.first) << " ";
        for (auto now_item : now_entrie.second) {
            std::cout << now_item << " ";
        }
        std::cout << std::endl;
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
    
    ModDefs mod_definitions;
    modify_definitions(definitions, default_defs, mod_definitions);
    print_defs(mod_definitions);
    
    auto search_1 = read_table(table_1, "table_1", mod_definitions, args_1);
    auto search_2 = read_table(table_2, "table_2", mod_definitions, args_2);
   
    print_table(table_1, "table_1");
    print_table(table_2, "table_2");

    auto out_file = open_out_file();
    print_header_l2(out_file, definitions, mod_definitions);

    parse_table(table_1, out_file, search_1, args_1, mod_definitions, "table_1");
    parse_table(table_2, out_file, search_2, args_2, mod_definitions, "table_2");

    out_file << "finish:" << std::endl;
    out_file.close();
}

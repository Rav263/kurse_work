#include <map>
#include <string>

#ifndef TABLE_IO
#define TEBLE_IO
using IP     = uint32_t; // IPv4
using Len    = int32_t;  // Prefix length
using Net_IP = std::pair<IP, Len>; // Prefix <IP, length>
using Port   = int32_t;  // Commutator 
using Table  = std::map<Net_IP, Port>; // map rules: Prefix -> port


uint32_t strip_to_int(std::string&);
std::string intip_to_string(std::pair<Net_IP, int>);
void print_table(Table &);
void read_table(std::string &, Table &);
#endif

#include <map>
#include <string>

using IP     = uint32_t;
using Net_IP = std::pair<IP, int>; 
using Table  = std::map<Net_IP, int>;


uint32_t strip_to_int(std::string&);
std::string intip_to_string(std::pair<Net_IP, int>);
void print_table(Table &);
void read_table(std::string &, Table &);

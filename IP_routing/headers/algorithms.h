#include "table_io.h"
#include "tree.h"


#ifndef ALGORITHMS
#define ALGORITHMS

std::pair<Net_IP, int> linary_search(Table &table, IP sr_ip);

Node *build_radix_tree(Table &table);
Node *build_patricia_tree(Table &table);

Net_IP find_node_radix(Node *now_node, IP sr_ip, uint32_t deph);
Net_IP find_node_patricia(Node *now_node, IP sr_ip, uint32_t deph);
#endif 

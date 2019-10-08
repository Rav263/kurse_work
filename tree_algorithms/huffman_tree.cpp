#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <utility>

using Data = int;

class Node {
    //Node *parrent;
    Node *left;
    Node *right;
    int weight;
    Data data;
public:
    Node(int weight, Data data):
        weight(weight), data(data) {
            this->left = nullptr;
            this->right = nullptr;
    }

    Node(Node *left, Node *right, int weight, Data data):
        left(left), right(right), weight(weight), data(data) {}

    Node *get_left() {
        return left;
    }

    Node *get_right() {
        return right;
    }

    int get_weight() {
        return weight;
    }
    
    Data get_data() {
        return data;
    }

    void set_left(Node *left) {
        this->left = left;
    }

    void set_right(Node *right) {
        this->right = right;
    }
    
    void set_data(Data data) {
        this->data = data;
    }

    bool operator< (const Node& now) const {
        return weight < now.weight;
    }
    int operator+ (const Node& now) const {
        return weight + now.weight;
    }
};



class HuffmanTree {
    Node *root;

public:
    HuffmanTree() {
        root = nullptr;
    }

    void add_node(std::pair<int, Data> probe) {
        if (root == nullptr) {
            root = new Node(nullptr, nullptr, probe.first, probe.second);
            return;
        }
        
    }
};


std::pair<int, int> get_minimals(std::vector<Node*> &nodes) {
    if (nodes.size() < 2) return {-1, -1};
    
    int min_index_1 = 0;
    int min_index_2 = 1;
    
    if (*nodes[min_index_2] < *nodes[min_index_1]) {
        int tmp = min_index_2;
        min_index_2 = min_index_1;
        min_index_1 = tmp;
    }

    for (int i = 2; i < nodes.size(); i++) {
        if (*nodes[i] < *nodes[min_index_1]) {
            min_index_2 = min_index_1;
            min_index_1 = i;
        } else if (*nodes[i] < *nodes[min_index_2]) {
            min_index_2 = i;
        }
    }

    return {min_index_1, min_index_2};
}

void print_node(Node *start, int height) {
    if (start == nullptr) return;
    for(int i = 0; i < height; i++) {
        std::cout << "::";
    }
    std::cout << " " << start->get_weight() << " " << start->get_data() << std::endl;
    print_node(start->get_left(), height + 1);
    print_node(start->get_right(), height + 1);
}

void read_probes(std::set<std::pair<int, Data>> &probes) {
    int probe;
    Data data;
    for(;std::cin >> probe >> data;) {
        probes.insert({probe, data});
    }
}

int main() {
    std::set<std::pair<int, Data>> probes;
    read_probes(probes);

    std::vector<Node *> nodes;

    for (auto probe : probes) {
        nodes.push_back(new Node(probe.first, probe.second));
    }

    while (nodes.size() > 1) {
        std::pair<int, int> indexes = get_minimals(nodes);

        Node *now = new Node(nodes[indexes.first],   nodes[indexes.second], 
                            *nodes[indexes.first] + *nodes[indexes.second], 0);

        if (indexes.first < indexes.second) {
            nodes.erase(nodes.begin() + indexes.first);
            nodes.erase(nodes.begin() + indexes.second - 1);
        } else {
            nodes.erase(nodes.begin() + indexes.second);
            nodes.erase(nodes.begin() + indexes.first - 1);
            
        }

        nodes.push_back(now);
    }
    print_node(nodes[0], 1);
}

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <tuple>


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

bool check_small(int i, int j, int k){
    return k*k < j - i + 1;
}


std::map<std::tuple<int, int,int>, std::pair<int, int>> table;

std::pair<int, int> calculate(int i, int j, int k, std::vector<int> &weights) {
    if (check_small(i, j, k)) return {-1,-1};
    if (i == j) return {0, -1};

    if (table.count({i, j, k}) > 0) return table[{i, j, k}];

    int result = 0;

    for (int t = i; t <= j; t++) {
        result += weights[t];
    }

    int value = -1;
    int breakpoint = -1;

    for (int b = i; b < j; b++) {
        auto fir = calculate(i, b, k - 1, weights).first;
        auto sec = calculate(b + 1,j, k - 1, weights).first;

        int tmp = fir == -1 or sec == -1 ? -1 : fir + sec;
        if (tmp == -1) continue;

        if (value == -1 or tmp < value) {
            breakpoint = b;
            value = tmp;
        }
    }
    if (value == -1) {
        result = -1;
    } else {
        result += value;
    }

    table[{i, j, k}] = {result, value};

    return {result, breakpoint};
}


Node *build_tree(int i, int j, int k, std::vector<int>& weights) {
    auto now = calculate(i, j, k, weights);
 //   std::cout << now.first << " " << now.second << std::endl;


    if (now.first == -1 or now.second == -1) return nullptr;
    int brp = now.second;

    return new Node(build_tree(i, brp, k - 1,  weights), build_tree(brp + 1, j, k - 1, weights), now.first, 0);
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

void free_tree(Node *now_node) {
    if (now_node == nullptr) return;

    free_tree(now_node->get_left());
    free_tree(now_node->get_right());

    delete now_node;
}

int main() {
    std::vector<int> weights;
    int k, n;

    std::cin >> k >> n;
    for (int i = 0; i < n; i++) {
        int now;
        Data data;
        //std::cin >> data;
        std::cin >> now;

        weights.push_back(now);
    }
    std::cout << "Building tree...";
    auto root = build_tree(1, n, k, weights);
    std::cout << "End" << std::endl;
    if (root == nullptr) {
        std::cout << "Can not build tree of this deph" << std::endl;
        return 0;
    }

    print_node(root, 1);

    free_tree(root);

    return 0;
}


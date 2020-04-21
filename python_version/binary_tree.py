from anytree import Node as AnNode
from anytree.exporter import DotExporter
import prefix_compare as pc


class Node:
    """Node class for AVL tree"""
    def __init__(self, left, right, prefix, port, depth):
        self.left = left
        self.right = right
        self.prefix = prefix
        self.port = port
        self.depth = depth

    def __str__(self):
        if self.prefix is not None:
            straa = pc.int_ip_to_str(self.prefix[0]) + "\\" + str(self.prefix[1])
        else:
            straa = ""
        straa += " depth: " + str(self.depth)
        return straa

    def generate_image(self, nodes, parent_index):
        if not len(nodes):
            nodes.append(AnNode(str(self)))
        else:
            nodes.append(AnNode(str(self) + " index: " + str(len(nodes)),
                         parent=nodes[parent_index]))

        now_index = len(nodes) - 1

        if self.left is not None:
            self.left.generate_image(nodes, now_index)
        if self.right is not None:
            self.right.generate_image(nodes, now_index)


def print_prefix(prefixes, end="\n", sep=" ", mod=pc.int_ip_to_str):
    for now in prefixes:
        print(mod(now[0]), now[1], end=sep)

    print(end=end)


def update_node_depth(node):
    depth = 0

    if node.right is not None:
        depth = node.right.depth
    if node.left is not None:
        depth = max(depth, node.left.depth)

    node.depth = depth + 1


def get_bit(prefix, bit):
    return format(prefix[0], "032b")[bit] == "1"


def add_node(entry, port, node, depth):
    if node is None:
        node = Node(None, None, None, None, 32 - depth)

    if depth == entry[1]:
        node.prefix = entry
        node.port = port
        node.depth = 32 - depth
        return node

    if get_bit(entry, depth):
        node.left = add_node(entry, port, node.left, depth + 1)
    else:
        node.right = add_node(entry, port, node.right, depth + 1)

    update_node_depth(node)

    return node


def find_prefix(node, prefix, depth):
    if node is None:
        return None

    if depth == 32:
        return node

    if get_bit(prefix, depth):
        tmp = find_prefix(node.left, prefix, depth + 1)
    else:
        tmp = find_prefix(node.right, prefix, depth + 1)

    if tmp is None and node.prefix is not None:
        return node
    else:
        return tmp


def build_binary_tree(table):
    root = None

    for now_entry in table:
        print(now_entry)
        root = add_node(now_entry, table[now_entry], root, 0)

    nodes = []
    root.generate_image(nodes, -1)
    print("Exporting image: ", end="")
    DotExporter(nodes[0]).to_picture("out.png")
    print("Done")

    while True:
        str_ip = input().strip()
        if str_ip == "end":
            break
        now_prefix = (pc.str_ip_to_int(str_ip), 32)
        node = find_prefix(root, now_prefix, 0)

        print_prefix([node.prefix, now_prefix])
        print_prefix([node.prefix, now_prefix], mod=bin)
        print_prefix([node.prefix, now_prefix], mod=int)

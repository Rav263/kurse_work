from anytree import Node as AnNode
from anytree.exporter import DotExporter
import prefix_compare as pc


class Node:
    """Node class for AVL tree"""
    def __init__(self, left, right, prefix, port, bit, depth):
        self.left = left
        self.right = right
        self.prefix = prefix
        self.port = port
        self.depth = depth
        self.bit = bit

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


def add_node(entry, port, node, bit):
    if node is None:
        node = Node(None, None, None, None, 32 - bit, 0)

    if bit == entry[1]:
        node.prefix = entry
        node.port = port
        node.bit = 32 - bit
        return node

    if get_bit(entry, bit):
        node.left = add_node(entry, port, node.left, bit + 1)
    else:
        node.right = add_node(entry, port, node.right, bit + 1)

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


def remove_bad_nodes(node):
    if node is None:
        return None

    node.left = remove_bad_nodes(node.left)
    node.right = remove_bad_nodes(node.right)

    if node.prefix is None:
        if node.left is not None and node.right is None:
            return node.left
        if node.right is not None and node.left is None:
            return node.right

    update_node_depth(node)

    return node


def balance_all_nodes(node):
    return node


def build_binary_compressed_tree(table):
    root = None

    for now_entry in table:
        print(now_entry)
        root = add_node(now_entry, table[now_entry], root, 0)

    root = remove_bad_nodes(root)

    nodes = []
    root.generate_image(nodes, -1)
    print(len(nodes))
    DotExporter(nodes[0]).to_picture("out.png")

"""AVL tree module"""
from anytree import Node as AnNode
import prefix_compare as pc
from anytree.exporter import DotExporter


class Node:
    """Node class for AVL tree"""
    def __init__(self, left, right, prefix, port, depth):
        self.left = left
        self.right = right
        self.prefix = prefix
        self.port = port
        self.depth = depth

    def __str__(self):
        # straa = pc.int_ip_to_str(self.prefix[0]) + "\\" + str(self.prefix[1])
        straa = str(pc.prefix_key(self.prefix)) + "\\" + str(self.prefix[1])
        straa += " " + str(self.depth)
        return straa

    def generate_image(self, nodes, parent_index):
        if not len(nodes):
            nodes.append(AnNode(str(self)))
        else:
            nodes.append(AnNode(str(self), parent=nodes[parent_index]))

        now_index = len(nodes) - 1

        if self.left is not None:
            self.left.generate_image(nodes, now_index)
        if self.right is not None:
            self.right.generate_image(nodes, now_index)


def update_node_depth(node):
    depth = 0

    if node.right is not None:
        depth = node.right.depth
    if node.left is not None:
        depth = max(depth, node.left.depth)

    node.depth = depth + 1


def left_rotate(node):
    right_node = node.right
    right_left_node = node.right.left

    right_node.left = node
    node.right = right_left_node

    update_node_depth(node)
    update_node_depth(right_node)

    return right_node


def right_rotate(node):
    left_node = node.left
    left_right_node = node.left.right

    left_node.right = node
    node.left = left_right_node

    update_node_depth(node)
    update_node_depth(left_node)

    return left_node


def get_node_balance(node):
    balance = 0

    if node.left is not None:
        balance = node.left.depth
    if node.right is not None:
        balance -= node.right.depth

    return balance


def add_node(entry, port, node):
    if node is None:
        return Node(None, None, entry, port, 1)

    if pc.prefix_key(entry) < pc.prefix_key(node.prefix):
        node.left = add_node(entry, port, node.left)
    else:
        node.right = add_node(entry, port, node.right)

    update_node_depth(node)

    balance = get_node_balance(node)

    # print(balance)
    entry_key = pc.prefix_key(entry)
    left_key = pc.prefix_key(node.left.prefix) if node.left is not None else 0
    right_key = pc.prefix_key(node.right.prefix) if node.right is not None else 0

    if balance > 1 and entry_key < left_key:
        return right_rotate(node)
    if balance < -1 and entry_key > right_key:
        return left_rotate(node)
    if balance > 1 and entry_key > left_key:
        node.left = left_rotate(node.left)
        return right_rotate(node)
    if balance < -1 and entry_key < right_key:
        node.right = right_rotate(node.right)
        return left_rotate(node)

    return node


def find_prefix(node, prefix):
    tmp = None
    if pc.prefix_key((prefix[0], node.prefix[1])) == pc.prefix_key(node.prefix):
        tmp = node
    if pc.prefix_key((prefix[0], node.prefix[1])) < pc.prefix_key(node.prefix):
        if node.left is not None:
            sec_tmp = find_prefix(node.left, prefix)
            return sec_tmp if sec_tmp is not None else tmp
        else:
            return tmp
    else:
        if node.right is not None:
            sec_tmp = find_prefix(node.right, prefix)
            return sec_tmp if sec_tmp is not None else tmp
        else:
            return tmp


def print_prefix(prefixes, end="\n", sep=" ", mod=pc.int_ip_to_str):
    for now in prefixes:
        print(mod(now[0]), now[1], end=sep)

    print(end=end)


def build_avl_tree(table, step=False):
    root = None
    entries = []
    for now_entry in table:
        entries.append(now_entry)

    entries = sorted(entries, key=pc.prefix_key)
    for x in entries:
        print(pc.prefix_key(x), pc.int_ip_to_str(x[0]), format(x[0], "032b"))

    counter = 1
    for now_entry in entries:
        # print(now_entry)
        root = add_node(now_entry, table[now_entry], root)

        if step:
            nodes = []
            root.generate_image(nodes, -1)
            DotExporter(nodes[0]).to_picture("outs/out_"+str(counter)+".png")
        counter += 1

    nodes = []
    root.generate_image(nodes, -1)
    print(len(nodes))
    DotExporter(nodes[0]).to_picture("out.png")

    while True:
        str_ip = input().strip()
        if str_ip == "end":
            break
        now_prefix = (pc.str_ip_to_int(str_ip), 32)
        node = find_prefix(root, now_prefix)

        print_prefix([node.prefix, now_prefix])
        print(format(pc.prefix_key(node.prefix), "032b"), node.prefix, format(pc.prefix_key(now_prefix), "032b"), now_prefix[1])
        print_prefix([now_prefix, node.prefix], mod=lambda x: format(x, "032b"))
        print_prefix([node.prefix, now_prefix], mod=int)

import prefix_compare as pc


class Node:
    def __init__(self, left, right, prefix, port, depth):
        self.left = left
        self.right = right
        self.prefix = prefix
        self.port = port
        self.depth = depth

    def __str__(self):
        straa = str(self.left) + "\n"
        straa += str(self.right) + "\n"
        straa += pc.int_ip_to_str(self.prefix[0]) + "\\"
        straa += str(self.prefix[1]) + " ===> " + str(self.port)
        return straa


def add_node(entry, port, node):
    if node is None:
        node = Node(None, None, entry, port, 1)
        return node

    if pc.prefix_compare(node.prefix, entry):
        node.left = add_node(entry, port, node.left)
    else:
        node.right = add_node(entry, port, node.right)

    return node


def build_avl_tree(table):
    root = None
    for now_entry in table:
        root = add_node(now_entry, table[now_entry], root)

    print(root)

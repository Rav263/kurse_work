#! /usr/bin/python3
from avl_tree import build_avl_tree


def main():
    print("start main")
    table = dict()

    table[(0, 32)] = 2
    table[(1, 32)] = 1
    table[(123, 32)] = 3

    build_avl_tree(table)


if __name__ == "__main__":
    print("This is ip routing tester and asm code generator")
    main()

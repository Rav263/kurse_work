#! /usr/bin/python3
"""This is module for generating asm code and testing trees"""
import sys
from avl_tree import build_avl_tree
from binary_tree import build_binary_tree
from binary_compressed_tree import build_binary_compressed_tree
from table_io import load_table


def print_help():
    print("Avalible args:")
    print("   -help                 -- print this message")
    print("   -tree  [avl, bct, bt] -- build one of three trees (avl, bct, bt)")
    print("   -table [path]         -- get table from file from [path]")


def parse_args() -> dict:
    """pasre function args"""
    dict_args = dict()
    for i in range(1, len(sys.argv)):
        if sys.argv[i] == "-table":
            dict_args["table"] = sys.argv[i + 1]
        if sys.argv[i] == "-tree":
            dict_args["tree"] = sys.argv[i + 1]
        if sys.argv[i] == "-help":
            dict_args["help"] = True
    return dict_args


def main(args: dict):
    """This is main function in project"""
    print("start main")
    if "help" in args:
        print_help()
        return None

    if "table" in args:
        table = load_table(args["table"])
    else:
        table = dict()
        for i in range(1, 16):
            table[(i*10, 32)] = 1

    print(table)

    if "tree" in args:
        if args["tree"] == "avl":
            build_avl_tree(table)
        elif args["tree"] == "bct":
            build_binary_compressed_tree(table)
        elif args["tree"] == "bt":
            build_binary_tree(table)
        else:
            print_help()
    else:
        print_help()


if __name__ == "__main__":
    print("This is ip routing tester and asm code generator")
    main(parse_args())

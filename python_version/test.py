#! /usr/bin/python3
"""test module"""

from random import shuffle
from tqdm import tqdm
import prefix_compare as pc


def max_prefix(table, start_index):
    max_prefix_index = start_index
    for i in range(start_index, len(table)):
        if pc.prefix_compare_3(table[i], table[max_prefix_index]) < 0:
            max_prefix_index = i

    return i


def sort_prefix(table):
    for i in range(len(table)):
        max_index = max_prefix(table, i)
        table[i], table[max_index] = table[max_index], table[i]
    return table


def print_table(table):
    print(*[(pc.int_ip_to_str(x), i) for x, i in table])


def print_prefix(prefixes, end="\n", sep=" ", mod=pc.int_ip_to_str):
    for now in prefixes:
        print(mod(now[0]), now[1], end=sep)

    print(end=end)


def main(mod):
    """main function for test"""
    if mod == 1:
        while True:
            str_ip_1, mask_1 = input("first prefix (ip mask): ").strip().split()
            str_ip_2, mask_2 = input("secon prefix (ip mask): ").strip().split()

            prefix_1 = (pc.str_ip_to_int(str_ip_1), int(mask_1))
            prefix_2 = (pc.str_ip_to_int(str_ip_2), int(mask_2))

            print(pc.prefix_compare(prefix_1, prefix_2))
    if mod == 2:
        file_name = input("please enter table_name: ").strip()

        table_file = open(file_name, "r")

        table = []

        for line in table_file:
            prefix = line.split()
            if not int(prefix[1]):
                continue
            prefix = (int(prefix[0]), int(prefix[1]))

            table.append(prefix)

        for now in table:
            tmp = pc.prefix_key(now)
            print(pc.int_ip_to_str(now[0]), now[1], tmp)

        print()

        # print_table(table)
        table_1 = sorted(table, key=pc.prefix_key)
        # print_table(table_1)
        shuffle(table)
        table_2 = sorted(table, key=pc.prefix_key)

        for now in enumerate(table_2):
            if now[1] != table_1[now[0]]:
                print_prefix((now[1], table_1[now[0]]), end=" === ")
                print(pc.prefix_key(now[1]), " === ", pc.prefix_key(table_1[now[0]]))

        run = [1]
        """
        for i in tqdm(range(10000)):
            shuffle(table)
            table_2 = sorted(table, key=pc.prefix_key)
            counter = 0
            for now in enumerate(table_2):
                if now[1] != table_1[now[0]]:
                    counter += 1

            run.append(counter)
        """
        print(*[(x, it) for it, x in enumerate(run) if x != 0])
        print("Average miss: ", sum(run) / len(run))
        print("total   miss: ", sum(run))


if __name__ == "__main__":
    MOD = input("please enter mode: ")
    main(int(MOD))

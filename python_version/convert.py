#! /usr/bin/python3
"""convert table module"""

import prefix_compare as pc


if __name__ == "__main__":
    while True:
        TMP = input().split()
        print(pc.int_ip_to_str(int(TMP[0])), int(TMP[1]))

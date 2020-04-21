"""bit prefix compare function"""


def get_bits(prefix, length):
    """function to get num of first prefix bits"""
    # print(prefix, length)
    tmp = format(prefix, "032b")[:length]
    # print(tmp)
    return int(tmp, 2)


def prefix_compare(prefix_1, prefix_2):
    """function to compare two prefixes"""
    pref_len = min(prefix_1[1], prefix_2[1])

    part_1 = get_bits(prefix_1[0], pref_len)
    part_2 = get_bits(prefix_2[0], pref_len)

    # print(part_1, part_2)
    # print(int_ip_to_str(part_1), "<",
    #      int_ip_to_str(part_2), "=")

    return part_1 < part_2


def prefix_compare_2(prefix_1, prefix_2):
    """test prefix compare function"""

    if prefix_1[0] == prefix_2[0]:
        pref_len = min(prefix_1[1], prefix_2[1])
        part_1 = get_bits(prefix_1[0], pref_len)
        part_2 = get_bits(prefix_2[0], pref_len)

        return part_1 < part_2
    return prefix_1[0] < prefix_2[0]


def get_mask(pref_len):
    return (((1 << 32) - 1) >> (32 - pref_len)) << (32 - pref_len)


def prefix_key(prefix):
    if prefix is None:
        return 0

    return prefix[0] & get_mask(prefix[1])


def prefix_compare_3(prefix_1, prefix_2):
    """an test prefix compare function"""

    key_1 = prefix_key(prefix_1)
    key_2 = prefix_key(prefix_2)

    return key_1 - key_2


def str_ip_to_int(str_ip):
    """function to get int value of str ip"""
    return sum(int(x) << 8 * (3 - i) for i, x in enumerate(str_ip.split(".")))


def int_ip_to_str(int_ip):
    """function to get str ip from int value"""
    return ".".join(reversed([str((int_ip >> 8 * i) & 255) for i in range(4)]))

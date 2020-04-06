def get_bits(prefix, length):
    tmp = format(prefix, "032b")[:length]
    print(tmp)
    return int(tmp, 2)


def prefix_compare(prefix_1, prefix_2):
    pref_len = min(prefix_1[1], prefix_2[1])

    part_1 = get_bits(prefix_1[0], pref_len - 1)
    part_2 = get_bits(prefix_2[0], pref_len - 1)

    print(part_1, part_2)
    print(int_ip_to_str(part_1), "<",
          int_ip_to_str(part_2))

    return part_1 < part_2


def str_ip_to_int(str_ip):
    return sum(int(x) << 8 * (3 - i) for i, x in enumerate(str_ip.split(".")))


def int_ip_to_str(int_ip):
    return ".".join(reversed([str((int_ip >> 8 * i) & 255) for i in range(4)]))

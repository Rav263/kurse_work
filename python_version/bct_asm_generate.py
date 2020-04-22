

def load_default_defenitions(file_name):
    defs = dict()

    defs_file = open(file_name, "r")

    for line in defs_file:
        words = line.strip().split()
        if len(words) == 0 or words[0][0] == "/":
            continue

        exec(words[1] + " = eval(str.join(' ', words[2:]))")

        defs[words[1]] = eval(words[1])

    defs_file.close()

    return defs


def load_table_args(file_name):
    args = dict()

    args_file = open(file_name, "r")

    for line in args_file:
        words = line.strip().split()

        if len(words) == 0:
            continue

    return args



def load_table(file_name):
    table_file = open(file_name, "r")

    table = dict()
    counter = 0

    for line in table_file:
        now = line.split()
        counter += 1

        if len(now) != 3:
            print("ERORR IN TABLE FILE IN LINE:", counter)

        table[(int(now[0]), int(now[1]))] = int(now[2])

    return table

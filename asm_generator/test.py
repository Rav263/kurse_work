string = "1234+(22<<13)+0x80"
new_string = ""
index = 0

while index < len(string):
    if (not string[index].isdigit()):
        new_string += string[index]
        index += 1
        continue

    if (index != len(string) - 1 and string[index + 1] == 'x'):
        new_string += string[index:index+2]
        index += 2
        while index < len(string):
            new_string += string[index]
            if not string[index].isdigit():
                break
            index += 1
    else:
        new_string += "8*"
        while index < len(string):
            new_string += string[index]
            if not string[index].isdigit():
                break
            index += 1
    index += 1
print(string)
print(new_string)

line = input().strip()

a = list()


while line != "0":
    if len(line) == 0:
        line = input().strip()
        continue

    a.append(line)
    line = input().strip()
    
print(*a)


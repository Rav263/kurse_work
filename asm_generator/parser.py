definitions = {}

while True:
    lines = input().split(" ")
    if (lines[0] == "end"): break
    if (lines[0] != "#define"): continue
    exec(lines[1] + " = eval(str.join(' ', lines[2:]))")
    
    definitions[lines[1]] = eval(lines[1])


for key in definitions:
    print(key, hex(definitions[key]))

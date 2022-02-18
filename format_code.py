import sys

def add_open_line(line):
    num_spaces = 0
    for char in line:
        if char == " ":
            num_spaces += 1
        else:
            break
    spaces = " "*num_spaces
    return "\n" + spaces + "{"

def add_close_line(line):
    num_spaces = 0
    for char in line:
        if char == " ":
            num_spaces += 1
        else:
            break
    spaces = " "*(num_spaces)
    # print(num_spaces)
    # print("AAAA")
    # print("--"+spaces+"--")
    # print("AAAA")
    return "}" + "\n" + spaces

name_to_format = sys.argv[1]

to_format = open(name_to_format, "r")
code = to_format.read()
to_format.close()

new_code = ""
for line in code.split("\n"):
    i = 0
    for char in line:
        if char == "{":
            new_code += add_open_line(line)
        elif char == "}":
            try:
                if line[i+1] != "\n":
                    new_code += add_close_line(line)
                # else:
                #     # new_code += " "
                #     new_code += "}"
            except IndexError:
                # new_code += " "
                new_code += "}"
        elif char == " " and line[i-1] == "}":
            pass
        elif char in "-+/*=<>":
            try:
                if line[i-1] == char or line[i+1] == char:
                    # == or ++ etc
                    new_code += char
                elif line[i+1] == "=":
                    # += or -= etc
                    new_code += char
                elif line[i-1] == " " and line[i+1] == " ":
                    # " + " or " - " etc
                    new_code += char
                elif char == "=" and line[i-1] in "-+/*<>!":
                    # -= or <= etc
                    new_code += char
                else:
                    new_code += " "
                    new_code += char
                    new_code += " "
            except IndexError:
                new_code += char
        else:
            new_code += char
        i += 1
    new_code += "\n"

# print(new_code)

new_new_code = ""
for line in new_code.split("\n"):
    num_spaces = 0
    for char in line:
        if char == " ":
            num_spaces += 1
        else:
            break
    new_num_spaces = round(num_spaces/4)*4
    new_new_code += " "*new_num_spaces
    new_new_code += line[num_spaces:]
    new_new_code += "\n"
print(new_new_code)
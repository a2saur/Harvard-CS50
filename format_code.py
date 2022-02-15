import sys

def add_open_line(line):
    num_spaces = 0
    for char in line:
        if char == " ":
            num_spaces += 1
        else:
            break
    spaces = " "*num_spaces
    return "\n" + spaces + "{" + spaces

def add_close_line(line):
    num_spaces = 0
    for char in line:
        if char == " ":
            num_spaces += 1
        else:
            break
    spaces = " "*(num_spaces-4)
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
            new_code += add_close_line(line)
        elif char in "-+/*":
            if line[i-1] == char or line[i+1] == char:
                new_code += char
            elif line[i+1] == "=":
                new_code += char
            else:
                new_code += " "
                new_code += char
                new_code += " "
        else:
            new_code += char
        i += 1
    new_code += "\n"

print(new_code)

# i = 0
# tabs = 0
# for char in code:
#     if char == "{":
#         new_code += "\n"
#         new_code += "-"*tabs
#         tabs += 1
#         new_code += char
#     elif char == "}":
#         try:
#             if code[i+1] == " ":
#                 tabs -= 1
#                 new_code += char
#                 new_code += "\n"
#                 new_code += "    "*tabs
#         except IndexError:
#             new_code += char
#     elif char in "+-*":
#         new_code += " "
#         new_code += char
#         new_code += " "
#     elif char == "/":
#         if code[i-1] == "/" or code[i+1] == "/":
#             new_code += char
#         else:
#             new_code += " "
#             new_code += char
#             new_code += " "
#     else:
#         new_code += char
#     i += 1
# print(new_code)
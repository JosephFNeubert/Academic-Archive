main_street = ["Smith", "Johnson", "Garcia", "Miller", "Lopez"]
string1 = ""
string2 = ""
string3 = ""

for i in main_street:
    string1 += i
print(string1)

for i in main_street[::2]:
    string2 += f"{i}, "
print(string2)

counter = 0
for i in main_street:
    counter += 1
    string3 += f"{i} ({counter} Main Str), "
string3 = string3[:-2]
print(string3)

house1 = main_street.pop(1)
house2 = main_street.pop(2)
main_street.insert(1, house2)
main_street.insert(3, house1)
print(main_street)

input1 = int(input("Enter an integer greater than  0: "))
for i in range(input1 + 1):
    temp_string = ""
    for x in range(1, i + 1):
        temp_string += f"{x} "
    print(temp_string)

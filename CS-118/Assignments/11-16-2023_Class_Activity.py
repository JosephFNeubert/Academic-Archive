"""Function 4 Test"""

# Problem 1
def item_sum(stuff: []) -> int:
    sum = 0
    for i in stuff:
        if isinstance(i, int):
            sum += i
        elif isinstance(i, list):
            sum += item_sum(i)
    return sum


mylist = [1, 2, 3, [10, 20, 30, [100, 200]], 4, 5]
print(item_sum(mylist))


# Problem 2
def is_power_of_three(n: int) -> bool:
    if n == 1:
        return True
    else:
        if n ** (1 / 3) % 1 == 0:
            return True
        else:
            return False


print(is_power_of_three(27))


# Problem 3
def dict_transform(d: {}, f: ()) -> {}:
    return {f(i) for i in d.values()}


d1 = {"a": 1, "b": 2, "c": 3}
print(dict_transform(d1, lambda x: x * 2))


# Problem 4
from sys import argv
from getpass import getuser


def write_doc_string(file_name: str, doc_string: str) -> None:
    text = ""
    with open(file_name) as f:
        text = f.read()
    if not text.strip().startswith('"""'):
        with open(file_name, "w") as f:
            f.write(f"{doc_string}\n\n{text}")


template = '"""Function 4 Test"""'
write_doc_string(argv[0], template)

from json import dump, load

# Json dumping and loading exercise
try:
    with open("data.json") as file:
        d = load(file)
        primes = d.get("primes")
        candidate = primes[-1]
except OSError as err:
    print(err)
    primes = [2]
    candidate = 1

primes = [2]
length = 100_000
candidate = 1
while len(primes) < length:
    candidate += 2
    for divisor in primes:
        if candidate % divisor == 0:
            break
        if divisor * divisor > candidate:
            primes.append(candidate)
            break

result = {"primes": primes}
try:
    with open("data.json", "w") as file:
        dump(result, file)
except OSError as err:
    print(err)

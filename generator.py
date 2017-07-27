import random, sys

x = int(sys.argv[1])

for i in range(x):
    r = random.randint(1, x)
    print(r)

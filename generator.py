import random, sys

x = int(sys.argv[1])

out = set([])

for i in range(x):
    out.add(random.randint(1, x))

for i in range(len(out)):
    print(i)

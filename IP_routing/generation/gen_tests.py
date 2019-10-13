import random
N = int(input())
K = int(input())

ips = set()

while len(ips) < N:
    ip   = random.randint(0, 2**32)
    mask = random.randint(0, 32)
    port = random.randint(0, K)

    ips.add((ip, mask, port))

for some in ips:
    print(some[0])
    print(some[1])
    print(some[2])

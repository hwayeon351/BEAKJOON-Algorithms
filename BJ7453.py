import sys
N = int(sys.stdin.readline())
A, B, C, D = [], [], [], []
for _ in range(N):
    a, b, c, d = map(int, sys.stdin.readline().split())
    A.append(a); B.append(b); C.append(c); D.append(d)

sum1 = dict()
for a in A:
    for b in B:
        sum1[a+b] = sum1.get(a+b, 0) + 1
cnt = 0
for c in C:
    for d in D:
        cnt += sum1.get(-(c+d), 0)
print(cnt)

import sys
input = sys.stdin.readline
N = int(input())
K = int(input())
if K >= N: print(0)
else:
    sensors = sorted(list(map(int, input().split())))
    dis = list()
    for i in range(N-1):
        dis.append(sensors[i+1]-sensors[i])
    dis.sort(reverse=True)
    print(sum(dis[K-1:]))

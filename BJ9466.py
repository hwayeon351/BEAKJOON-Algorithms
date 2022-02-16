import sys
from collections import defaultdict
sys.setrecursionlimit(200001)
input = sys.stdin.readline

def dfs(now):
    global team
    visit[now] = 1
    route.append(now)
    if visit[choice[now]]:
        if choice[now] in route:
            team += route[route.index(choice[now]):]
            return
    else: dfs(choice[now])


T = int(input())
for _ in range(T):
    n = int(input())
    choice = [0] + list(map(int, input().split()))
    team = list()
    visit = [0] * (n + 1)
    for i in range(1, n+1):
        if not visit[i]:
            route = []
            dfs(i)
    print(n-len(team))

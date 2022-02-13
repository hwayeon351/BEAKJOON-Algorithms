import sys
from collections import defaultdict
sys.setrecursionlimit(500001)
input = sys.stdin.readline

def dfs(v):
    for nv in graph[v]:
        if not visit[nv]:
            visit[nv] = 1
            dfs(nv)

N, M = map(int, input().split())
graph = defaultdict(list)
for _ in range(M):
    u, v = map(int, input().split())
    graph[u].append(v)
    graph[v].append(u)

cnt = 0
visit = [0]*(N+1)
for v in range(1, N+1):
    if not visit[v]:
        visit[v] = 1
        dfs(v)
        cnt += 1
print(cnt)

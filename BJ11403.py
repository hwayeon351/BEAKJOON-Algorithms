import sys
sys.setrecursionlimit(10001)

def dfs(now, j):
    global visit
    for v, e in enumerate(graph[now]):
        if e and not visit[v]:
            visit[v] = 1
            dfs(v, j)

input = sys.stdin.readline
N = int(input())
graph = []
for _ in range(N):
    graph.append(list(map(int, input().split())))

for i in range(N):
    line = ""
    for j in range(N):
        visit = [0] * N
        dfs(i, j)
        if visit[j]: line += "1 "
        else: line += "0 "
    print(line)

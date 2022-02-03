import sys
from collections import deque
global dfs_result, bfs_result
dfs_result, bfs_result = "", ""
def DFS(now, visit, edge):
    global dfs_result
    dfs_result += (str(now) + " ")
    visit[now] = 1
    next = sorted(edge[now][:])
    for n in next:
        if visit[n]: continue
        DFS(n, visit, edge)

def BFS(V, edge, visit):
    global bfs_result
    q = deque([V])
    while q:
        now = q.popleft()
        if visit[now]: continue
        visit[now] = 1
        bfs_result += (str(now) + " ")
        next = sorted(edge[now][:])
        for n in next:
            if visit[n]: continue
            q.append(n)

input = sys.stdin.readline
N, M, V = map(int, input().split())
edge = [[] for _ in range(N+1)]
for _ in range(M):
    v1, v2 = map(int, input().split())
    edge[v1].append(v2)
    edge[v2].append(v1)
visit = [0]*(N+1)
DFS(V, visit, edge)
visit = [0]*(N+1)
BFS(V, edge, visit)
print(dfs_result)
print(bfs_result)

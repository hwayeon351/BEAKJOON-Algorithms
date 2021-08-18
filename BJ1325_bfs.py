import sys
from collections import deque, defaultdict

N, M = map(int, sys.stdin.readline().split())
graph = defaultdict(list)

for _ in range(M):
    v1, v2 = map(int, sys.stdin.readline().split())
    graph[v2].append(v1)

def bfs(s):
    q = deque()
    q.append(s)
    visit = [0] * (N+1)
    visit[s] = 1
    counts[s] = 1
    while q:
        now_v = q.popleft()
        for nv in graph[now_v]:
            if not visit[nv]:
                visit[nv] = 1
                counts[s] += 1
                q.append(nv)

max_cnt = 0
counts = [0]*(N+1)
for i in range(1, N+1):
    bfs(i)
    if counts[i] > max_cnt: max_cnt = counts[i]

for i, cnt in enumerate(counts):
    if cnt == max_cnt:
        print(i, end=' ')

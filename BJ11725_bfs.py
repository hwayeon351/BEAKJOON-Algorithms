import sys
from collections import defaultdict
from collections import deque
N = int(sys.stdin.readline())
tree = defaultdict(list)
parent = defaultdict(int)

for _ in range(N-1):
    v1, v2 = map(int, sys.stdin.readline().split())
    tree[v1].append(v2)
    tree[v2].append(v1)
    
def bfs():
    q = deque()
    q.append(1)
    while q:
        now_v = q.popleft()
        for nv in tree[now_v]:
            if parent[nv] == 0:
                parent[nv] = now_v
                q.append(nv)
bfs()
for i in range(2, N+1):
    print(parent[i])

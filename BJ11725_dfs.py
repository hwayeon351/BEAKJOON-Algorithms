import sys
from collections import defaultdict
sys.setrecursionlimit(3000000)
N = int(sys.stdin.readline())
tree = defaultdict(list)
for _ in range(N-1):
    v1, v2 = map(int, sys.stdin.readline().split())
    tree[v1].append(v2)
    tree[v2].append(v1)
    
parent = defaultdict(int)

def dfs(v, tree, parent):
    for nv in tree[v]:
        if parent[nv] == 0:
            parent[nv] = v
            dfs(nv, tree, parent)
dfs(1, tree, parent)           
for i in range(2, N+1):
    print(parent[i])

import sys
from collections import defaultdict, deque
def find_relationship(p1, p2):
    visit = [0]*(n+1)
    visit[p1] = 1
    q = deque([[p1, 0]])

    while q:
        p, cnt = q.popleft()
        if p == p2:
            print(cnt)
            return
        for np in graph[p]:
            if not visit[np]:
                q.append([np, cnt+1])
                visit[np] = 1
    print(-1)

input = sys.stdin.readline
n = int(input())
p1, p2 = map(int, input().split())
m = int(input())
graph = defaultdict(list)

for _ in range(m):
    parent, child = map(int, input().split())
    graph[parent].append(child)
    graph[child].append(parent)

find_relationship(p1, p2)

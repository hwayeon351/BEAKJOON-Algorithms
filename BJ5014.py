import sys
from collections import deque

input = sys.stdin.readline
F, S, G, U, D = map(int, input().split())

q = deque([[S, 0]])
visit = [0]*(F+1)
visit[S] = 1
while q:
    now, cnt = q.popleft()
    if now == G:
        print(cnt)
        break
    if now+U <= F and not visit[now+U]:
        visit[now+U] = 1
        q.append([now+U, cnt+1])
    if now-D >= 1 and not visit[now-D]:
        visit[now-D] = 1
        q.append([now-D, cnt+1])
if now != G: print("use the stairs")

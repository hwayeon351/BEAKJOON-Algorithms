import sys
from collections import deque
def bfs(sx, sy, ex, ey):
    visit = [[0]*I for _ in range(I)]
    q = deque([[sx, sy, 0]])
    visit[sy][sx] = 1
    while q:
        x, y, cnt = q.popleft()
        if x == ex and y == ey:
            print(cnt)
            return
        for ddx, ddy in zip(dx, dy):
            nx, ny = x+ddx, y+ddy
            if 0 <= nx < I and 0 <= ny < I and not visit[ny][nx]:
                visit[ny][nx] = 1
                q.append([nx, ny, cnt+1])


input = sys.stdin.readline
T = int(input())
dx = [-2, -1, 1, 2, -2, -1, 1, 2]
dy = [-1, -2, -2, -1, 1, 2, 2, 1]
for _ in range(T):
    I = int(input())
    sx, sy = map(int, input().split())
    ex, ey = map(int, input().split())
    bfs(sx, sy, ex, ey)

import sys
from collections import deque

def move():
    q = deque([[0, 0, 1, 0]])
    visit = [[[0]*M for _ in range(N)] for _ in range(2)]
    visit[0][0][0] = 1
    while q:
        x, y, cnt, broken = q.popleft()
        if x == M-1 and y == N-1:
            print(cnt)
            return
        for ddx, ddy in zip(dx, dy):
            nx, ny = x+ddx, y+ddy
            if 0 <= nx < M and 0 <= ny < N:
                if not visit[broken][ny][nx]:
                    if _map[ny][nx] == '0':
                        q.append([nx, ny, cnt+1, broken])
                        visit[broken][ny][nx] = 1
                    elif not broken:
                        q.append([nx, ny, cnt+1, 1])
                        visit[1][ny][nx] = 1
    print(-1)

input = sys.stdin.readline
N, M = map(int, input().split())
dx = [-1, 0, 1, 0]
dy = [0, -1, 0, 1]
_map = list()
for _ in range(N):
    _map.append(list(input().rstrip()))

move()

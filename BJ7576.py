import sys
from collections import deque
imput = sys.stdin.readline
M, N = map(int, input().split())
box = list()
q = deque(list())
for i in range(N):
    box.append(list(map(int, input().split())))
    for j in range(M):
        if box[i][j] == 1: q.append([j, i, 0])
if not q: print(-1)
else:
    dx = [-1, 0, 1, 0]
    dy = [0, -1, 0, 1]
    while q:
        x, y, day = q.popleft()
        for ddx, ddy in zip(dx, dy):
            nx = x + ddx
            ny = y + ddy
            if 0 <= nx < M and 0 <= ny < N and box[ny][nx] == 0:
                box[ny][nx] = 1
                q.append([nx, ny, day+1])
    for row in box:
        if 0 in row:
            print(-1)
            break
    else:
        print(day)

import sys
from collections import deque

def BFS(sx, sy, miro, N, M):
    dx = [-1, 0, 1, 0]
    dy = [0, -1, 0, 1]
    visit = [[0]*(M+1) for _ in range(N+1)]
    visit[sy][sx] = 1
    q = deque([[sx, sy, 1]])
    while q:
        x, y, cnt = q.popleft()
        if y == N and x == M:
            print(cnt)
            return
        for i in range(4):
            nx = x + dx[i]
            ny = y + dy[i]
            if 0 <= nx <= M and 0 <= ny <= N:
                if not visit[ny][nx] and miro[ny][nx]:
                    visit[ny][nx] = 1
                    q.append([nx, ny, cnt+1])


input = sys.stdin.readline
N, M = map(int, input().split())
miro = list()
for _ in range(N):
    miro.append(list(map(int, input().strip())))
BFS(0, 0, miro, N-1, M-1)

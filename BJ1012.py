import sys
sys.setrecursionlimit(10000)
input = sys.stdin.readline

def dfs(x, y):
    for ddx, ddy in zip(dx, dy):
        nx, ny = x+ddx, y+ddy
        if 0 <= nx < M and 0 <= ny < N and not visit[ny][nx] and area[ny][nx]:
            visit[ny][nx] = 1
            dfs(nx, ny)

T = int(input())
dx = [-1, 0, 1, 0]
dy = [0, -1, 0, 1]
for _ in range(T):
    M, N, K = map(int, input().split())
    area = [[0]*M for _ in range(N)]
    worms = 0
    for _ in range(K):
        x, y = map(int, input().split())
        area[y][x] = 1
    visit = [[0] * M for _ in range(N)]
    for y in range(N):
        for x in range(M):
            if area[y][x] and not visit[y][x]:
                visit[y][x] = 1
                dfs(x, y)
                worms += 1
    print(worms)

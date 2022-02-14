import sys
sys.setrecursionlimit(10001)
input = sys.stdin.readline

def dfs(x, y):
    global size
    size += 1
    for ddx, ddy in zip(dx, dy):
        nx = x+ddx
        ny = y+ddy
        if 1 <= nx <= M and 1 <= ny <= N and graph[ny][nx] and not visit[ny][nx]:
            visit[ny][nx] = 1
            dfs(nx, ny)

N, M, K = map(int, input().split())
graph = [[0]*(M+1) for _ in range(N+1)]
for _ in range(K):
    y, x = map(int, input().split())
    graph[y][x] = 1
visit = [[0]*(M+1) for _ in range(N+1)]
dx = [-1, 0, 1, 0]
dy = [0, -1, 0, 1]
answer = 0

for y in range(1, N+1):
    for x in range(1, M+1):
        if graph[y][x] and not visit[y][x]:
            global size
            size = 0
            visit[y][x] = 1
            dfs(x, y)
            if answer < size: answer = size
print(answer)

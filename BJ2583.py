import sys
sys.setrecursionlimit(10001)
def dfs(x, y):
    global answer
    answer += 1
    for ddx, ddy in zip(dx, dy):
        nx, ny = x+ddx, y+ddy
        if 0 <= nx <N and 0 <= ny < M and not paper[ny][nx] and not visit[ny][nx]:
            visit[ny][nx] = 1
            dfs(nx, ny)

input = sys.stdin.readline
M, N, K = map(int, input().split())
paper = [[0]*N for _ in range(M)]
for _ in range(K):
    sx, sy, ex, ey = map(int, input().split())
    for x in range(sx, ex):
        for y in range(sy, ey):
            paper[y][x] = 1

visit = [[0]*N for _ in range(M)]
dx = [-1, 0, 1, 0]
dy = [0, -1, 0, 1]
answer = 0
area = 0
result = []
for y in range(M):
    for x in range(N):
        if visit[y][x] + paper[y][x] == 0:
            answer = 0
            visit[y][x] = 1
            dfs(x, y)
            result.append(answer)
            area += 1
print(area)
result.sort()
for r in result:
    print(r, end=' ')

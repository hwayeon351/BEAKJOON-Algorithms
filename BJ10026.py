import sys
sys.setrecursionlimit(20000)
input = sys.stdin.readline
def dfs(x, y, color):
    for ddx, ddy in zip(dx, dy):
        nx = x+ddx
        ny = y+ddy
        if 0 <= nx < N and 0 <= ny < N and picture[ny][nx] == color and not visit[ny][nx]:
            visit[ny][nx] = 1
            dfs(nx, ny, color)

def blind_dfs(x, y, color):
    for ddx, ddy in zip(dx, dy):
        nx = x+ddx
        ny = y+ddy
        if 0 <= nx < N and 0 <= ny < N and not visit[ny][nx]:
            if (color == picture[ny][nx]) or (color == 'R' and picture[ny][nx] == 'G') or (color == 'G' and picture[ny][nx] == 'R'):
                visit[ny][nx] = 1
                blind_dfs(nx, ny, color)

N = int(input())
picture = []
for _ in range(N):
    picture.append(list(input().rstrip()))

dx = [-1, 0, 1, 0]
dy = [0, -1, 0, 1]

normal_area = 0
visit = [[0]*N for _ in range(N)]
for y in range(N):
    for x in range(N):
        if not visit[y][x]:
            visit[y][x] = 1
            dfs(x, y, picture[y][x])
            normal_area += 1

blind_area = 0
visit = [[0]*N for _ in range(N)]
for y in range(N):
    for x in range(N):
        if not visit[y][x]:
            visit[y][x] = 1
            blind_dfs(x, y, picture[y][x])
            blind_area += 1
print(normal_area, blind_area)

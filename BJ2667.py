import sys
def dfs(x, y):
    global num
    num += 1
    for ddx, ddy in zip(dx, dy):
        nx = x+ddx
        ny = y+ddy
        if 0 <= nx < N and 0 <= ny < N and _map[ny][nx] == '1' and not visit[ny][nx]:
            visit[ny][nx] = 1
            dfs(nx, ny)

input = sys.stdin.readline
N = int(input())
_map = list()
for _ in range(N):
    _map.append(list(input().rstrip()))
visit = [[0]*N for _ in range(N)]
dx = [-1, 0, 1, 0]
dy = [0, -1, 0, 1]
area = 0
houses = list()
num = 0
for y in range(N):
    for x in range(N):
        if _map[y][x] == '1' and not visit[y][x]:
            num = 0
            visit[y][x] = 1
            dfs(x, y)
            houses.append(num)
            area += 1
print(area)
for num in sorted(houses):
    print(num)

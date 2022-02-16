import sys
sys.setrecursionlimit(20000)
input = sys.stdin.readline

def dfs(x, y, h):
    global visit
    for ddx, ddy in zip(dx, dy):
        nx = x + ddx
        ny = y + ddy
        if 0 <= nx < N and 0 <= ny < N and area[ny][nx] > h and not visit[ny][nx]:
            visit[ny][nx] = 1
            dfs(nx, ny, h)

N = int(input())
area = []
max_area = 0
max_height = 0
dx = [-1, 0, 1, 0]
dy = [0, -1, 0, 1]

for _ in range(N):
    row = list(map(int, input().split()))
    area.append(row)
    highest = max(row)
    if max_height < highest: max_height = highest

for h in range(max_height+1):
    visit = [[0]*N for _ in range(N)]
    now_area = 0
    for y in range(N):
        for x in range(N):
            if area[y][x] > h and not visit[y][x]:
                visit[y][x] = 1
                dfs(x, y, h)
                now_area += 1
    if now_area > max_area: max_area = now_area
print(max_area)

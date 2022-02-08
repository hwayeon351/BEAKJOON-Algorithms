import sys
from collections import deque

def fill_up_water():
    edge = len(water)
    while edge:
        x, y = water.popleft()
        for ddx, ddy in zip(dx, dy):
            nx, ny = x+ddx, y+ddy
            if 0 <= nx < C and 0 <= ny < R and forest[ny][nx] == '.':
                forest[ny][nx] = '*'
                water.append([nx, ny])
        edge -= 1

def escape():
    while q:
        fill_up_water()

        edge = len(q)
        while edge:
            x, y, mins = q.popleft()
            if forest[y][x] == 'D':
                print(mins)
                return
            for ddx, ddy in zip(dx, dy):
                nx, ny = x + ddx, y + ddy
                if 0 <= nx < C and 0 <= ny < R:
                    if (forest[ny][nx] == '.' or forest[ny][nx] == 'D') and not visit[ny][nx]:
                        visit[ny][nx] = 1
                        q.append([nx, ny, mins+1])
            edge -= 1
    print("KAKTUS")
    return

input = sys.stdin.readline
R, C = map(int, input().split())
dx = [-1, 0, 1, 0]
dy = [0, -1, 0, 1]
forest = []
q = deque(list())
water = deque(list())
visit = [[0]*C for _ in range(R)]
for r in range(R):
    forest.append(list(input().rstrip()))
    for c in range(C):
        if forest[r][c] == 'S':
            q.append([c, r, 0])
            visit[r][c] = 1
            forest[r][c] = '.'
        elif forest[r][c] == '*':
            water.append([c, r])
escape()

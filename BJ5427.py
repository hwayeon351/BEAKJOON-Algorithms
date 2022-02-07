import sys
from collections import deque

def spread_fire():
    size = len(fires)
    while size:
        x, y = fires.popleft()
        for ddx, ddy in zip(dx, dy):
            nx = x + ddx
            ny = y + ddy
            if 0 <= nx < w and 0 <= ny < h and building[ny][nx] == '.':
                fires.append([nx, ny])
                building[ny][nx] = '*'
        size -= 1

def BFS():
    while q:
        spread_fire()
        edge = len(q)
        while edge:
            x, y, sec = q.popleft()
            for ddx, ddy in zip(dx, dy):
                nx = x + ddx
                ny = y + ddy
                if 0 <= nx < w and 0 <= ny < h:
                    if building[ny][nx] == '.' and not visit[ny][nx]:
                        q.append([nx, ny, sec+1])
                        visit[ny][nx] = 1
                else: return sec + 1
            edge -= 1
    return 0


input = sys.stdin.readline
T = int(input())
dx = [-1, 0, 1, 0]
dy = [0, -1, 0, 1]
building = []
fires = deque(list())
q = deque(list())
for _ in range(T):
    w, h = map(int, input().split())
    building.clear()
    fires.clear()
    q.clear()
    visit = [[0]*w for _ in range(h)]
    for hh in range(h):
        building.append(list(input()))
        for ww in range(w):
            if building[hh][ww] == '@':
                q.append([ww, hh, 0])
                visit[hh][ww] = 1
                building[hh][ww] = '.'
            if building[hh][ww] == '*':
                fires.append([ww, hh])
    result = BFS()
    if result > 0: print(result)
    else: print("IMPOSSIBLE")

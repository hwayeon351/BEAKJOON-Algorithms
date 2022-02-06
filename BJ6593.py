import sys
from collections import deque

input = sys.stdin.readline
L, R, C = map(int, input().split())
building = list()
q = deque(list())
dl = [0, 0, 0, 0, 1, -1]
dr = [-1, 0, 1, 0, 0, 0]
dc = [0, -1, 0, 1, 0, 0]
answer = []

while L+R+C > 0:
    q.clear()
    building.clear()
    visit = [[[0] * C for _ in range(R)] for _ in range(L)]
    for l in range(L):
        floor = list()
        for r in range(R):
            floor.append(list(input().rstrip()))
            for c in range(C):
                if floor[r][c] == 'S':
                    q.append([l, r, c, 0])
                    floor[r][c] = '.'
                    visit[l][r][c] = 1
        building.append(floor)
        input()
    while q:
        l, r, c, mins = q.popleft()
        if building[l][r][c] == 'E':
            answer.append("Escaped in %d minute(s)." %mins)
            break
        for ddl, ddr, ddc in zip(dl, dr, dc):
            nl = l + ddl
            nr = r + ddr
            nc = c + ddc
            if 0 <= nl < L and 0 <= nr < R and 0 <= nc < C:
                if not visit[nl][nr][nc] and building[nl][nr][nc] != '#':
                    visit[nl][nr][nc] = 1
                    q.append([nl, nr, nc, mins+1])
    else: answer.append("Trapped!")
    L, R, C = map(int, input().split())

for ans in answer:
    print(ans)

from collections import deque, defaultdict
import sys, copy
def puzzle_to_str(puzzle):
    str_q = ""
    for row in puzzle:
        str_q += "".join(map(str, row))
    return str_q
def play(x, y):
    visit = defaultdict(int)
    q = deque([[copy.deepcopy(puzzle), 0, x, y]])
    visit[puzzle_to_str(puzzle)] = 1

    while q:
        pz, cnt, zx, zy = q.popleft()
        if puzzle_to_str(pz) == "123456780":
            print(cnt)
            return
        for ddx, ddy in zip(dx, dy):
            nzx = zx+ddx
            nzy = zy+ddy
            if 0 <= nzx < 3 and 0 <= nzy < 3:
                pz[zy][zx], pz[nzy][nzx] = pz[nzy][nzx], pz[zy][zx]
                str_pz = puzzle_to_str(pz)
                if visit[str_pz] == 0:
                    visit[str_pz] = 1
                    q.append([copy.deepcopy(pz), cnt+1, nzx, nzy])
                pz[zy][zx], pz[nzy][nzx] = pz[nzy][nzx], pz[zy][zx]

    print(-1)

input = sys.stdin.readline
puzzle = list()
dx = [-1, 0, 1, 0]
dy = [0, -1, 0, 1]
for y in range(3):
    puzzle.append(list(map(int, input().split())))
    for x in range(3):
        if puzzle[y][x] == 0:
            zx, zy = x, y
play(zx, zy)

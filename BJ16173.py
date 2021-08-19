import sys
def dfs(x, y):
    global ck
    if ck: return
    if x>=N or y>=N: return
    if x==N-1 and y==N-1:
        ck = True
        return
    jump = area[y][x]
    if jump == 0: return
    dfs(x+jump, y)
    dfs(x, y+jump)

N = int(sys.stdin.readline())
area = []
ck = False
for _ in range(N):
    area.append(list(map(int, sys.stdin.readline().split())))
dfs(0, 0)
if ck: print("HaruHaru")
else: print("Hing")

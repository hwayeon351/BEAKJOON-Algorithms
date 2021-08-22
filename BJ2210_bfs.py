import sys
from collections import deque
def bfs(sx, sy):
    global nums
    q = deque()
    q.append([sx, sy, board[sy][sx]])
    while q:
        x, y, num = q.popleft()
        if len(num) == 6:
            nums.add(num)
            continue
        for i in range(4):
            nx = x+dx[i]
            ny = y+dy[i]
            if 0<=nx<5 and 0<=ny<5:
                q.append([nx, ny, num+board[ny][nx]])

global nums
board = []
dx = [-1, 0, 1, 0]
dy = [0, -1, 0, 1]
nums = set()

for _ in range(5):
    board.append(sys.stdin.readline().split())

for i in range(5):
    for j in range(5):
        bfs(i, j)

print(len(nums))

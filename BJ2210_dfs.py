import sys
def dfs(cnt, x, y, num):
    global nums
    if cnt == 6:
        nums.add(num)
        return

    for i in range(4):
        nx = x+dx[i]
        ny = y+dy[i]
        if 0<=nx<5 and 0<=ny<5:
            dfs(cnt+1, nx, ny, num+board[ny][nx])
    
global nums
board = []
dx = [-1, 0, 1, 0]
dy = [0, -1, 0, 1]
nums = set()
for _ in range(5):
    board.append(list(sys.stdin.readline().split()))
for i in range(5):
    for j in range(5):
        dfs(1, j, i, board[i][j])
print(len(nums))

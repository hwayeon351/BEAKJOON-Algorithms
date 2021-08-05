def find_route(board, dp):
    for x in range(n):
        for y in range(n):
            if dp[y][x]>0 and board[y][x]>0:
                r_nx, r_ny = x+board[y][x], y
                b_nx, b_ny = x, y+board[y][x]
                if r_nx<n and r_ny<n:
                    dp[r_ny][r_nx] += dp[y][x]
                if b_nx<n and b_ny<n: 
                    dp[b_ny][b_nx] += dp[y][x]


n = int(input()) 
board = []
for i in range(n):
    board.append(list(map(int, input().split())))
dp = [[0]*n for i in range(n)]
dp[0][0] = 1
find_route(board, dp)
print(dp[-1][-1])

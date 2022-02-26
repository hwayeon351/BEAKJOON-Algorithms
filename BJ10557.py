import sys
N = int(sys.stdin.readline())
dp = [[0]*10 for _ in range(1001)]
for i in range(10):
    dp[1][i] = 1

for n in range(2, N+1):
    for i in range(10):
        cnt = 0
        for j in range(i, 10):
            cnt += dp[n-1][j]
        dp[n][i] = cnt

answer = 0
for i in range(10):
    answer += dp[N][i]
print(answer%10007)

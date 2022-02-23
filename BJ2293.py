import sys
input = sys.stdin.readline
n, k = map(int, input().split())
coin = [int(input()) for _ in range(n)]

dp = [0]*(k+1)
dp[0] = 1
for c in coin:
    for won in range(c, k+1):
        dp[won] += dp[won-c]
print(dp[k])

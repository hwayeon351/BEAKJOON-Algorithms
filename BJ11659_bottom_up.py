import sys
N, M = map(int, sys.stdin.readline().split())
nums = list(map(int, sys.stdin.readline().split()))
nums = [0] + nums
dp = [0]*(N+1)
for i in range(1, N+1):
    dp[i] = dp[i-1] + nums[i]

for _ in range(M):
    i, j = map(int, sys.stdin.readline().split())
    print(dp[j]-dp[i-1])

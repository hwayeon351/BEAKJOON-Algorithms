import sys
sys.setrecursionlimit(200000)
N, M = map(int, sys.stdin.readline().split())
nums = list(map(int, sys.stdin.readline().split()))
nums = [0] + nums
def cal_dp(i):
    if i == 0: return 0
    if dp[i] != 0:
        return dp[i]
    dp[i] = cal_dp(i-1) + nums[i]
    return dp[i]

dp = [0]*(N+1)

for _ in range(M):
    i, j = map(int, sys.stdin.readline().split())
    print(cal_dp(j)-cal_dp(i-1))

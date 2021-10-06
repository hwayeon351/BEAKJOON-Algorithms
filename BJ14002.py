import sys
N = int(sys.stdin.readline())
A = list(map(int, sys.stdin.readline().split()))
dp = [1]*N
subset = [[num] for num in A]

for i in range(N):
    for j in range(0, i):
        if A[i] > A[j]:
            if dp[i] < dp[j] + 1:
                dp[i] = dp[j] + 1
                subset[i] = subset[j] + [A[i]]

max_i = 0
for i in range(N):
    if dp[max_i] < dp[i]: max_i = i
print(dp[max_i])
print(*subset[max_i])

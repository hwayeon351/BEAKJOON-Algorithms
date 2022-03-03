import sys
input = sys.stdin.readline
N, K = map(int, input().split())
product = []
for _ in range(N):
    product.append(list(map(int, input().split())))
dp = [0]*(K+1)
for W, V in product:
    for i in range(K, W-1, -1):
        dp[i] = max(dp[i], dp[i-W] + V)
print(dp[-1])

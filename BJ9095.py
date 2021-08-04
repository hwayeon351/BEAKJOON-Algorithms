def solution(n):
    if n <= 2: return n
    elif n == 3: return 4
    dp = [0]*(n+1)
    dp[1] = 1
    dp[2] = 2
    dp[3] = 4
    for i in range(4, n+1):
        dp[i] = dp[i-1] + dp[i-2] + dp[i-3]
    return dp[n]
n = int(input())
answer = [0]*n
for i in range(n):
    answer[i] = solution(int(input()))
for i in range(n):
    print(answer[i])

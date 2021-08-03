def solution(n):
    if n == 1: return 0
    elif n <= 3: return 1
    dp = [0]*(n+1)
    dp[2] = 1
    dp[3] = 1
    for i in range(4, n+1):
        a, b = i-1, i-1
        if i%3==0:
            a = min(a, 1+dp[i//3])
        if i%2==0:
            b = min(b, 1+dp[i//2])
        dp[i] = min(a, b, 1+dp[i-1])
    return dp[n]
n = input()
print(solution(int(n)))

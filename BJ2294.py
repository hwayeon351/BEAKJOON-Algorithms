import sys
sys.setrecursionlimit(200000)
def get_coin_cnt(won):
    if not visit[won]:
        cnt = -1
        for coin in coins:
            if won >= coin:
                a = get_coin_cnt(coin)
                b = get_coin_cnt(won-coin)
                if a == -1 or b == -1: continue
                if cnt == -1 or a+b < cnt: cnt = a+b
        dp[won] = cnt
        visit[won] = True
    return dp[won]

n, k = map(int, sys.stdin.readline().split())
coins = list(set([int(sys.stdin.readline()) for _ in range(n)]))
coins.sort(reverse=True)
dp = [-1]*max(k+1, coins[0]+1)
dp[0] = 0
visit = [False]*max(k+1, coins[0]+1)
for coin in coins:
    dp[coin] = 1
    visit[coin] = True
print(get_coin_cnt(k))

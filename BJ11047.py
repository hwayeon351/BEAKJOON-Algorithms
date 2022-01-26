import sys
def get_minimum_cnt(N, K, coin):
    total = 0
    money = K
    for i in range(N-1, -1, -1):
        cnt = money//coin[i]
        if cnt > 0:
            total += cnt
            money %= coin[i]
            if money == 0: break
    return total

input = sys.stdin.readline
N, K = map(int, input().split())
coin = list()
for _ in range(N):
    coin.append(int(input()))
print(get_minimum_cnt(N, K, coin))

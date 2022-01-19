import sys
def get_withdrawal(money, M):
    left = max(money)
    right = max(money)*len(money)
    answer = right
    while left <= right:
        mid = (left+right)//2
        wallet = 0
        cnt = 0
        for m in money:
            if m <= wallet:
                wallet -= m
            else:
                if cnt >= M: break
                wallet = mid - m
                cnt += 1
        else:
            answer = min(answer, mid)
            right = mid-1
            continue
        left = mid+1
    return answer

input = sys.stdin.readline
N, M = map(int, input().split())
money = list()
for _ in range(N):
    money.append(int(input()))
print(get_withdrawal(money, M))

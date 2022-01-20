import sys

def get_length(K, N, lans):
    left = 1
    right = max(lans)
    answer = 0
    while left <= right:
        mid = (left+right)//2
        cnt = 0
        for lan in lans:
            cnt += (lan//mid)
        if cnt >= N:
            answer = mid
            left = mid+1
        else:
            right = mid-1
    return answer

input = sys.stdin.readline
K, N = map(int, input().split())
lans = list()
for _ in range(K):
    lans.append(int(input()))
print(get_length(K, N, lans))

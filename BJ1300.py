import sys

def find_kth_number(N, k):
    left = 1
    right = N*N
    while left <= right:
        mid = (left+right)//2
        cnt = 0
        for i in range(1, N+1):
            cnt += min(mid//i, N)
        if cnt >= k: right = mid - 1
        else: left = mid + 1
    return left

input = sys.stdin.readline
N = int(input())
k = int(input())
print(find_kth_number(N, k))

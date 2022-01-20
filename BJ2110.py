import sys

def find_router_loc(N, C, houses):
    left = 1
    right = houses[-1] - houses[0]
    while left <= right:
        mid = (left + right)//2
        cur = houses[0]
        cnt = 1
        for i in range(1, N):
            if cur + mid <= houses[i]:
                cur = houses[i]
                cnt += 1
        if cnt >= C:
            left = mid+1
            answer = mid
        else:
            right = mid-1
    return answer

input = sys.stdin.readline
N, C = map(int, input().split())
houses = list()
for _ in range(N):
    houses.append(int(input()))
houses.sort()
print(find_router_loc(N, C, houses))

import sys

def getLimit(left, right, areas, N, M):
    answer = min(left, right)
    while left <= right:
        mid = (left+right)//2
        total = 0
        for area in areas:
            total += min(area, mid)
        if total > M:
            right = mid-1
        else:
            answer = mid
            left = mid + 1
    return answer

input = sys.stdin.readline
N = int(input())
areas = list(map(int, input().split()))
M = int(input())
left = min(min(areas), M//N)
right = max(areas)
print(getLimit(left, right, areas, N, M))

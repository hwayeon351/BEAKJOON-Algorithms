import sys
from bisect import bisect_left
input = sys.stdin.readline
N = int(input())
arr = list(map(int, input().split()))
lis = []
for num in arr:
    if len(lis) == 0: lis.append(num)
    else:
        loc = bisect_left(lis, num)
        if loc >= len(lis):
            lis.append(num)
        else:
            lis[loc] = num
print(len(lis))

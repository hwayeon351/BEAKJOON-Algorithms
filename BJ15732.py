import sys
def find_last_box(N, K, D, rules):
    left = 1
    right = N
    while left <= right:
        mid = (left+right)//2
        cnt = 0
        for start, end, step in rules:
            if start > mid: continue
            if mid > end:
                cnt += ((end-start)//step + 1)
            else:
                cnt += ((mid-start)//step + 1)
            if cnt >= D:
                right = mid-1
                answer = mid
                break
        else:
            left = mid+1
    return answer

input = sys.stdin.readline
N, K, D = map(int, input().split())
rules = list()
for _ in range(K):
    rules.append(list(map(int, input().split())))
print(find_last_box(N, K, D, rules))

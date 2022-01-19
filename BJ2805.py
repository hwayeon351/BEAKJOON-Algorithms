import sys
def find_height(left, right, trees, M):
    answer = 0
    while left <= right:
        mid = (left+right)//2
        total = 0
        for t in trees:
            if t > mid:
                total += (t-mid)
        if total >= M:
            answer = max(answer, mid)
            left = mid + 1
        else:
            right = mid - 1
    return answer

input = sys.stdin.readline
N, M = map(int, input().split())
trees = list(map(int, input().split()))
left = 0
right = max(trees)
print(find_height(left, right, trees, M))

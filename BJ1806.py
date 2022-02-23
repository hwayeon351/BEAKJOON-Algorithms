import sys
input = sys.stdin.readline
N, S = map(int, input().split())
arr = list(map(int, input().split()))

left = 0
right = 0
n_sum = 0
answer = 0

while True:
    if left > right or right == N: break
    n_sum += arr[right]
    if n_sum >= S:
        length = right - left + 1
        if answer == 0 or length < answer:
            answer = length
        n_sum -= (arr[left] + arr[right])
        left += 1
    else:
        right += 1
print(answer)

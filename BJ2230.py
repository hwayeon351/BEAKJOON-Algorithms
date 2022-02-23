import sys
input = sys.stdin.readline
N, M = map(int, input().split())
A = [int(input()) for _ in range(N)]
A.sort()

left = 0
right = 1
answer = 0

while True:
    if left >= N-1 or right == N: break
    diff = A[right] - A[left]
    if diff >= M:
        if diff == M:
            answer = M
            break

        if answer == 0 or diff < answer:
            answer = diff
        left += 1

    else:
        right += 1

print(answer)

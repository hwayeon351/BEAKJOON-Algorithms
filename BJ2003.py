import sys
input = sys.stdin.readline
N, M = map(int, input().split())
A = list(map(int, input().split()))

start = 0
end = 0
n_sum = 0
answer = 0

while True:
    if start >= N: break

    n_sum += A[end]
    if n_sum == M:
        answer += 1
        n_sum -= (A[start]+A[end])
        start += 1

    elif n_sum > M:
        n_sum -= (A[start]+A[end])
        start += 1

    else:
        if end == N-1:
            n_sum -= (A[start]+A[end])
            start += 1
        else:
            end += 1

print(answer)

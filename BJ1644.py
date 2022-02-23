import math
def is_prime_number():
    for n in range(2, int(math.sqrt(N+1))+1):
        if is_prime[n]:
            for nn in range(2*n, N+1, n):
                is_prime[nn] = False

N = int(input())
is_prime = [True]*(N+1)
is_prime_number()
primes = [i for i in range(2, N+1) if is_prime[i]]

start = 0
end = 0
n_sum = 0
answer = 0
while True:
    if start == len(primes) or end == len(primes): break
    n_sum += primes[end]
    if n_sum == N:
        answer += 1
        n_sum -= primes[start]
        start += 1
        end += 1
    elif n_sum < N:
        end += 1
    else:
        n_sum -= (primes[start]+primes[end])
        start += 1

print(answer)

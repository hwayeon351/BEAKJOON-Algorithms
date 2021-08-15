T = int(input())
for _ in range(T):
    N = int(input())
    stock = list(map(int, input().split()))
    earn = 0
    max_p = stock[-1]
    for i in range(N-2, -1, -1):
        if stock[i] > max_p:
            max_p = stock[i]
        else:
            earn += max_p-stock[i]
    print(earn)

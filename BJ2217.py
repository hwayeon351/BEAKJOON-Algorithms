import sys
def get_maximum_weight(N, rope):
    weight = rope[0]
    cnt = 1
    for i in range(1, N):
        if rope[i]*(i+1) > weight:
            weight = rope[i]*(i+1)
            cnt += 1
    print(weight)

input = sys.stdin.readline
N = int(input())
rope = list()
for _ in range(N):
    rope.append(int(input()))
rope.sort(reverse=True)
get_maximum_weight(N, rope)

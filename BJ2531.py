import sys
from collections import Counter
input = sys.stdin.readline

N, d, k, c = map(int, input().split())

belts = []
for _ in range(N):
    belts.append(int(input()))

start = 0
end = k-1
cnt = k
susi = set(belts[:k])
counter = Counter(belts[:k])
max_cnt = len(susi)
while start < N:
    if cnt == k:
        kinds = len(susi)
        if counter[c] == 0: kinds += 1
        if kinds > max_cnt: max_cnt = kinds

        counter[belts[start]] -= 1
        if counter[belts[start]] == 0: susi.remove(belts[start])
        start += 1
        cnt -= 1
    end = (end + 1) % N
    cnt += 1
    susi.add(belts[end])
    counter[belts[end]] += 1
print(max_cnt)

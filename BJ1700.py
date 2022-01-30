import sys
from collections import Counter
input = sys.stdin.readline
N, K = map(int, input().split())
uses = list(map(int, input().split()))
counter = Counter(uses)
taps = list()
cnt = 0
for i in range(K):
    if uses[i] in taps:
        counter[uses[i]] -= 1
        continue
    if len(taps) < N:
        counter[uses[i]] -= 1
        taps.append(uses[i])
    #하나 뽑아야 하는 경우,
    else:
        for j in range(N):
            if counter[taps[j]] == 0:
                taps[j] = uses[i]
                counter[uses[i]] -= 1
                break
        else:
            idx = [-1, -1]
            for j in range(N):
                for k in range(i+1, K):
                    if taps[j] == uses[k]:
                        if idx[0] == -1 or idx[1] < k:
                            idx[0] = j
                            idx[1] = k
                        break
            taps[idx[0]] = uses[i]
            counter[uses[i]] -= 1
        cnt += 1
print(cnt)

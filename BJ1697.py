import sys
from collections import deque
def find_sis(N, K):
    q = deque([[N, 0]])
    visit = [0]*100001
    visit[N] = 1
    while q:
        loc, sec = q.popleft()
        if loc == K:
            print(sec)
            return
        if 0 <= loc-1 and not visit[loc-1]:
            visit[loc-1] = 1
            q.append([loc-1, sec+1])
        if loc+1 <= 100000 and not visit[loc+1]:
            visit[loc+1] = 1
            q.append([loc+1, sec+1])
        if 0 <= loc*2 <= 100000 and not visit[loc*2]:
            visit[loc*2] = 1
            q.append([loc*2, sec+1])

input = sys.stdin.readline
N, K = map(int, input().split())
find_sis(N, K)

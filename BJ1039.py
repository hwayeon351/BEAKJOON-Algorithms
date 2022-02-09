import sys
from collections import deque
def make_num():
    q = deque([[str(N), K]])
    visit = [[0]*1000001 for _ in range(K)]
    answer = -1
    while q:
        str_n, cnt = q.popleft()
        if cnt == 0:
            if answer < int(str_n): answer = int(str_n)
            continue
        for i in range(len(str_n)-1):
            for j in range(i+1, len(str_n)):
                if i == 0 and str_n[j] == '0': continue
                new_n = str_n[:i] + str_n[j] + str_n[i+1:j] + str_n[i] + str_n[j+1:]
                if not visit[cnt-1][int(new_n)]:
                    q.append([new_n, cnt-1])
                    visit[cnt-1][int(new_n)] = 1
    return answer
input = sys.stdin.readline
N, K = map(int, input().split())
print(make_num())

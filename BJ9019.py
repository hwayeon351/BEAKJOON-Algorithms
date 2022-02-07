import sys
from collections import deque
def BFS(A, B, visit, q):
    q.append([A, ""])
    visit[A] = 1
    while q:
        a, cmd = q.popleft()
        if a == B:
            return cmd
        #D
        new_a = (a*2) % 10000
        if not visit[new_a]:
            q.append([new_a, cmd+"D"])
            visit[new_a] = 1

        #S
        if a == 0: new_a = 9999
        else: new_a = a-1
        if not visit[new_a]:
            q.append([new_a, cmd+"S"])
            visit[new_a] = 1

        #L
        str_a = str(a).zfill(4)
        new_a = int((str_a[1]+str_a[2]+str_a[3]+str_a[0]))
        if not visit[new_a]:
            q.append([new_a, cmd+"L"])
            visit[new_a] = 1

        #R
        new_a = int((str_a[3]+str_a[0]+str_a[1]+str_a[2]))
        if not visit[new_a]:
            q.append([new_a, cmd+"R"])
            visit[new_a] = 1

input = sys.stdin.readline
T = int(input())
visit = [0]*10001
q = deque(list())

for _ in range(T):
    visit = [0] * 10001
    q.clear()
    A, B = list(map(int, input().split()))
    print(BFS(A, B, visit, q))

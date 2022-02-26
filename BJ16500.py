import sys
sys.setrecursionlimit(20001)
def solution(idx):
    global answer
    if idx == len(S):
        answer = 1
        return
    if visit[idx]: return
    visit[idx] = 1
    for i in range(len(A)):
        if len(S[idx:]) >= len(A[i]):
            for j in range(len(A[i])):
                if A[i][j] != S[idx+j]:
                    break
            else: solution(idx+len(A[i]))
answer = 0
S = sys.stdin.readline().rstrip()
N = int(sys.stdin.readline())
A = [sys.stdin.readline().rstrip() for _ in range(N)]
visit = [0]*len(S)
solution(0)
print(answer)

import sys
def find_dna(dna, N, M):
    dis = 0
    answer = ""
    for i in range(M):
        cnt = {'A': 0, 'C': 0, 'G': 0, 'T': 0}
        for j in range(N):
            cnt[dna[j][i]] += 1
        answer += max(cnt.keys(), key=lambda x:cnt[x])
        dis += (sum(cnt.values())-cnt[answer[-1]])
    print(answer)
    print(dis)

input = sys.stdin.readline
N, M = map(int, input().split())
dna = list()
for _ in range(N):
    dna.append(input())
find_dna(dna, N, M)

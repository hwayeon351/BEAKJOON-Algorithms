import sys
def get_max_score(homework, N):
    day = homework[0][0]
    visit = [0]*N
    score = 0
    while day > 0:
        i = -1
        for j in range(N):
            if visit[j]: continue
            if homework[j][0] >= day:
                if i == -1: i = j
                elif homework[j][1] > homework[i][1]: i = j
        if i != -1:
            visit[i] = 1
            score += homework[i][1]
        day -= 1
    print(score)

input = sys.stdin.readline
N = int(input())
homework = list()
for _ in range(N):
    homework.append(list(map(int, input().split())))
homework.sort(reverse = True)
get_max_score(homework, N)

N = int(input())
dw = [[0,0] for _ in range(N)]
visit = [0]*N
for i in range(N):
    dw[i] = list(map(int, input().split()))
dw.sort(reverse = True)
timer = dw[0][0]
total = 0
while timer > 0:
    idx = -1
    for i in range(N):
        if dw[i][0] < timer: break
        if visit[i] == 0:
            if idx == -1: idx = i
            elif dw[idx][1] < dw[i][1]: idx = i
    if idx != -1:
        visit[idx] = 1
        total += dw[idx][1]
    timer-=1
print(total)

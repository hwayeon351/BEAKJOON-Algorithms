N = int(input())
crane = list(map(int, input().split()))
M = int(input())
box = list(map(int, input().split()))
if max(crane) < max(box): print(-1)
else:
    crane.sort(reverse = True)
    box.sort(reverse = True)
    time = 0
    b_visit = [0]*M
    c_pos = [0]*N
    cnt = 0
    while cnt < M:
        time += 1
        for c in range(N):
            while c_pos[c] < M:
                #박스 옮길 수 있는 경우,
                if not b_visit[c_pos[c]] and box[c_pos[c]] <= crane[c]:
                    b_visit[c_pos[c]] = 1
                    c_pos[c] += 1
                    cnt += 1
                    break
                c_pos[c] += 1
    print(time)

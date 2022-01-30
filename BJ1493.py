import sys, math
def get_cube_cnt(l, w, h, N, cube):
    box = [[l, w, h]]
    cnt = 0
    while box:
        L, W, H = box.pop()
        if L == 0 or W == 0 or H == 0: continue
        for i in range(N-1, -1, -1):
            length = cube[i][0]
            if length == 1:
                n = L*W*H
                if n <= cube[i][1]:
                    cnt += n
                    cube[i][1] -= n
                    break
            elif length <= L and length <= W and length <= H and cube[i][1] > 0:
                cube[i][1] -= 1
                cnt += 1
                box.append([L-length, W, length])
                box.append([length, W-length, length])
                box.append([L, W, H-length])
                break
        else:
            print(-1)
            return
    print(cnt)

input = sys.stdin.readline
l, w, h = map(int, input().split())
N = int(input())
cube = list()
for _ in range(N):
    a, b = map(int, input().split())
    cube.append([2**a, b])

get_cube_cnt(l, w, h, N, cube)

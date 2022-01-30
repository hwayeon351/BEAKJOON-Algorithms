import sys
def get_cube_cnt(l, w, h, N, cube):
    box = [[l, w, h]]
    cnt = 0
    while box:
        L, W, H = box.pop()
        if L == 0 or W == 0 or H == 0: continue
        for i in range(N-1, -1, -1):
            d = 2**cube[i][0]
            if d <= L and d <= W and d <= H and cube[i][1] > 0:
                cube_cnt = min(L//d, W//d, H//d, cube[i][1])
                cube[i][1] -= cube_cnt**3
                length = d*cube_cnt
                cnt += cube_cnt**3
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
    cube.append(list(map(int, input().split())))
get_cube_cnt(l, w, h, N, cube)

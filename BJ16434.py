import sys
from math import ceil
def get_max_HP(N, s_atk, rooms):
    left = 1
    right = N*1000000000000
    while left <= right:
        mid = (left+right)//2
        soldier_HP = mid
        soldier_atk = s_atk
        dead = False
        for i in range(N):
            t, a, h = rooms[i]
            #몬스터 방
            if t == 1:
                cnt = ceil(h/soldier_atk)-1
                soldier_HP -= cnt*a
                if soldier_HP <= 0:
                    dead = True
            #포션 방
            else:
                soldier_HP += h
                if soldier_HP > mid: soldier_HP = mid
                soldier_atk += a

            if dead: break

        if dead:
            left = mid + 1

        else:
            answer = mid
            right = mid - 1
    return answer

input = sys.stdin.readline
N, s_atk = map(int, input().split())
rooms = list()
for _ in range(N):
    rooms.append(list(map(int, input().split())))
print(get_max_HP(N, s_atk, rooms))

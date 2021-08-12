N, C = map(int, input().split())
M = int(input())
box_info = []
truck_capa = [C]*(N+1)
for _ in range(M):
    box_info.append(list(map(int, input().split())))
box_info.sort(key = lambda x:x[1])
b_cnt = 0
for i in range(M):
    min_box = C
    for town in range(box_info[i][0], box_info[i][1]):
        if truck_capa[town] < min_box: min_box = truck_capa[town]
    min_box = min(min_box, box_info[i][2])
    b_cnt += min_box
    for town in range(box_info[i][0], box_info[i][1]):
        truck_capa[town] -= min_box
print(b_cnt)

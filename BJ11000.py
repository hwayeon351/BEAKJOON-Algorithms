import sys
import heapq
def get_lecture_rooms(N, lectures):
    rooms = list()
    heapq.heappush(rooms, lectures[0][1])
    for i in range(1, N):
        if rooms[0] <= lectures[i][0]:
            heapq.heappop(rooms)
        heapq.heappush(rooms, lectures[i][1])
    print(len(rooms))

input = sys.stdin.readline
N = int(input())
lectures = list()
for _ in range(N):
    lectures.append(list(map(int, input().split())))
lectures.sort()
get_lecture_rooms(N, lectures)

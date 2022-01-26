import sys
def get_maximum_cnt(N, meetings):
    start = meetings[0][0]
    end = meetings[0][1]
    cnt = 1
    for i in range(1, N):
        if end > meetings[i][1]:
            start = meetings[i][0]
            end = meetings[i][1]
        elif end <= meetings[i][0]:
            cnt += 1
            start = meetings[i][0]
            end = meetings[i][1]
    print(cnt)

input = sys.stdin.readline
N = int(input())
meetings = list()
for _ in range(N):
    meetings.append(list(map(int, input().split())))
meetings.sort()
get_maximum_cnt(N, meetings)

import sys
def get_maximum_cnt(N, meetings):
    start = meetings[0][0]
    end = meetings[0][1]
    cnt = 1
    for i in range(1, N):
        #이전 회의가 i번째 회의보다 늦게 끝나는 경우, i번째 회의를 선택한다
        if end > meetings[i][1]:
            start = meetings[i][0]
            end = meetings[i][1]
        #이전 회의가 i번째 회의보다 빨리 끝나는 경우,
        #이전 회의가 끝난 이후 i번째 회의가 시작되는 경우, i번째 회의를 선택한다
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

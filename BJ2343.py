import sys
def get_bluelay_size(M, lectures):
    left = 0
    right = sum(lectures)
    answer = right
    while left <= right:
        mid = (left+right)//2
        bluelay = [0]*M
        i = 0
        for lec in lectures:
            if lec + bluelay[i] <= mid:
                bluelay[i] += lec
            else:
                i += 1
                # 블루레이에 다 못 담는 경우
                if i == M or lec > mid: break
                bluelay[i] += lec
        else:
            answer = min(answer, mid)
            right = mid-1
            continue
        left = mid+1
    return answer

input = sys.stdin.readline
N, M = map(int, input().split())
lectures = list(map(int, input().split()))
print(get_bluelay_size(M, lectures))

import sys
def get_tape_cnt(L, leaks):
    tape_start = leaks[0]-0.5
    cnt = 0
    for l in leaks:
        if tape_start < l < tape_start+L:
            continue
        cnt += 1
        tape_start = l-0.5
    return cnt+1

input = sys.stdin.readline
N, L = map(int, input().split())
leaks = list(map(int, input().split()))
leaks.sort()
print(get_tape_cnt(L, leaks))

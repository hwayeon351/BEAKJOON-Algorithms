import sys
input = sys.stdin.readline
while True:
    try:
        xx = int(input())*(10**7)
        n = int(input())
        lego = []
        for _ in range(n):
            lego.append(int(input()))
        lego.sort()
        check = False
        left = 0
        right = n-1
        while left < right:
            sum = lego[left] + lego[right]
            if sum == xx:
                check = True
                print('yes', lego[left], lego[right])
                break
            elif sum < xx:
                left += 1
            elif sum > xx:
                right -= 1
        if not check: print('danger')
    except: break

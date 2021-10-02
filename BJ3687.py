T = int(input())
answer = []
dp = [0, 0, [1, 1], [7, 7], [4, 11], [2, 71], [6, 111], [8, 711], [10, 1111], [18, 7111], [22, 11111]]
p = ['8', '10', '18', '200', '20', '28', '68']
for _ in range(T):
    n = int(input())
    if n < len(dp):
        answer.append(dp[n])
        continue
    if n%2==0:
        max = '1'*(n//2)
    else:
        max = '7' + '1'*((n-3)//2)
    pivot = n%7
    if pivot == 3:
        min =  p[pivot] + '8'*(n//7-2)
        answer.append([int(min), int(max)])
        continue
    #pivot: 0, 1, 2, 4, 5
    min = p[pivot]+'8'*(n//7-1)
    answer.append([int(min), int(max)])
for i in range(len(answer)):
    print(answer[i][0], answer[i][1])

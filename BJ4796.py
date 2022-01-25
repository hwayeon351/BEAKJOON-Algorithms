import sys
input = sys.stdin.readline
L, P, V = map(int, input().split())
result = list()
while (L+P+V) > 0:
    result.append(V//P*L+min(V % P, L))
    L, P, V = map(int, input().split())

for i in range(len(result)):
    print("Case %d: %d" %(i+1, result[i]))

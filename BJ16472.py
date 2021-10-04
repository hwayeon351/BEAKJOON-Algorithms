N = int(input())
text = input()
if len(text) == 1:
    print(1)
elif len(set(text)) <= N:
    print(len(text))
else:
    left = 0
    right = 1
    sets = set([text[left]])
    ans = 0
    while left < len(text)-1:
        if right == len(text):
            ans = max(ans, right-left)
            break
        sets.add(text[right])
        if len(sets) == N:
            ans = max(ans, right-left+1)
            right += 1
        elif len(sets) > N:
            sets.clear()
            left += 1
            sets.add(text[left])
            right = left + 1
        else:
            right += 1
    print(ans)

import sys, heapq
def union_cards(cards, m):
    while m > 0:
        nsum = heapq.heappop(cards) + heapq.heappop(cards)
        m -= 1
        heapq.heappush(cards, nsum)
        heapq.heappush(cards, nsum)
    print(sum(cards))
input = sys.stdin.readline
n, m = map(int, input().split())
cards = list(map(int, input().split()))
heapq.heapify(cards)
union_cards(cards, m)

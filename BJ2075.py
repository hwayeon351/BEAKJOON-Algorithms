import heapq, sys
N = int(sys.stdin.readline())
heap = []
for _ in range(N):
    row = list(map(int, sys.stdin.readline().split()))
    if len(heap) == 0:
        for num in row:
            heapq.heappush(heap, num)
    else:
        for num in row:
            if heap[0] < num:
                heapq.heappop(heap)
                heapq.heappush(heap, num)
print(heap[0])

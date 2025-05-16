T = int(input())

for i in range(1, T+1):
    N, M = map(int, input().split())
    graph = [list(map(int, input().split())) for _ in range(N)]
    prefix = [[0] * (N+1) for _ in range(N+1)]
    ans = 0

    for x in range(1, N+1):
        for y in range(1, N+1):
            prefix[x][y] = prefix[x-1][y] + prefix[x][y-1] - prefix[x-1][y-1] + graph[x-1][y-1]

    for x in range(M, N+1):
        for y in range(M, N+1):
            result = prefix[x][y] - prefix[x-M][y] - prefix[x][y-M] + prefix[x-M][y-M]
            ans = max(ans, result)

    print(f"#{i} {ans}")

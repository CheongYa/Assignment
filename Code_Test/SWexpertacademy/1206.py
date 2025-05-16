for testcase in range(1, 11):
    N = int(input())
    building =list(map(int, input().split()))
    ans = 0

    for i in range(2, N-2):
        left_best = max(building[i-1], building[i-2])
        right_best = max(building[i+1], building[i+2])
        best = max(left_best, right_best)
        
        if building[i] > best:
            ans += building[i] - best
    
    print(f"#{testcase} {ans}")
T = int(input())

for i in range(1, T+1):
    num = list(map(int, input().split()))
    ans = 0
    for j in num:
        if j % 2 == 1:
            ans += j
    print(f"#{i} {ans}")
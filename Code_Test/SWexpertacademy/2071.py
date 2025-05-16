T = int(input())

for i in range(1, T+1):
    nums = list(map(int, input().split()))
    ans = 0
    
    for num in nums:
        ans += num
    
    print(f"#{i} {round(ans / 10)}")
T = int(input())

for testcase in range(1, T+1):
    num = int(input())
    li = list(map(int, input().split()))
    max_price = 0
    ans = 0

    for price in reversed(li):
        if price > max_price:
            max_price = price
        else:
            ans += max_price - price
    
    print(f"#{testcase} {ans}")
T = int(input())

for i in range(T):
    num = int(input())
    scores = list(map(int, input().split()))

    li = [0] * 101
    for j in scores:
        li[j] += 1

    max_score = max(li)

    for j in range(100, -1, -1):
        if li[j] == max_score:
            print(f"#{num} {j}")
            break
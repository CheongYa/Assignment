n = int(input())

for _ in range(n):
    s = input()
    score = 0
    cnt = 0
    for c in s:
        if c == 'O':
            cnt += 1
            score += cnt
        else:
            cnt = 0
    print(score)
t = int(input())

for _ in range(t):
    r, s = input().split()
    r = int(r)
    print(''.join([char * r for char in s])) # 각 문자를 r만큼 반복

# 혹은

t = int(input())

for i in range(t):
    r, s = input().split()
    r = int(r)
    for j in range(len(s)):
        print(s[j] * r, end = '')
    print('')
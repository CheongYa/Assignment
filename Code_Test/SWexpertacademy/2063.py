N = int(input())
li = list(map(int, input().split()))

li.sort()
print(li[round(N/2) - 1])

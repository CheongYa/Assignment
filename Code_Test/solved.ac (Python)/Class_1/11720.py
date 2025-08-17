n = int(input())
total = 0

total += sum(map(int, input().strip()))

print(total)

# 혹은

n = input()
nums = input()
total = 0
for i in nums :
    total += int(i)
print(total)
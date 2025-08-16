numbers = []

for _s in range(9):
   num = int(input())
   numbers.append(num)

print(max(numbers))
print(numbers.index(max(numbers)) + 1)

# 혹은

numbers = [int(input()) for _ in range(9)]

print(max(numbers))
print(numbers.index(max(numbers)) + 1)
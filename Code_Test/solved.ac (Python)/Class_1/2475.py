a = map(int, input().split())
print(sum(x**2 for x in a) % 10) # 설명: a의 각 요소를 제곱한 값을 모두 더한 후 10으로 나눈 나머지를 구함

# 혹은

num = map(int, input().split())
result = 0

for i in num:
   result += i ** 2

print(result%10)
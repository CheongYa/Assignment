a = int(input())
b = int(input())
c = int(input())
num = a*b*c

count = [0] * 10

for digit in str(num):
    count[int(digit)] += 1

# 결과 출력
for i in range(10):
    print(count[i])
a = int(input())
b = int(input())
c = int(input())

num = a * b * c
num_str = str(num)

for i in range(10):
    print(num_str.count(str(i)))
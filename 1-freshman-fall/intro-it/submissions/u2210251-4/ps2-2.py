from math import factorial
x = int(input())
for i in range(x):
    for j in range(x - i + 1):
        print(end=" ")
    for j in range(i + 1):
        z = (factorial(i))//(factorial(i - j)*factorial(j))
        print(z, end=" ")
    print()
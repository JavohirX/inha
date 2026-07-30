x = []
y = []
for num in range(1, 10000):

    for divisor in range(1, num + 1):

        if num % divisor == 0:

            if divisor not in y:

                y.append(divisor)

    if sum(y) / 2 == num:

        x.append(num)

y = []

print(x)

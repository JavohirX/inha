from math import sqrt

class Fractions:
    def findGCD(n1, n2):
        gcd = 0
        for i in range(1, int(min(n1, n2)) + 1):
            if n1 % i == 0 and n2 % i == 0:
                gcd = i
        return gcd


    # input first fraction
    num1, den1 = map(int, list(input("Enter numerator and denominator of first number : ").split(" ")))

    # input first fraction
    num2, den2 = map(int, list(input("Enter numerator and denominator of second number: ").split(" ")))

    lcm = (den1 * den2) // findGCD(den1, den2)
    sum = (num1 * lcm // den1) + (num2 * lcm // den2)

    num3 = sum // findGCD(sum, lcm)

    lcm = lcm // findGCD(sum, lcm)

    print(num1, "/", den1, " + ", num2, "/", den2, " = ", num3, "/", lcm)

class Sets:
    A = {0, 2, 4, 6, 8};
    B = {1, 2, 3, 4, 5};
    print("Union :", A | B)
    print("Intersection :", A & B)
    print("Difference :", A - B)
    print("Symmetric difference :", A ^ B)

class Vectors:
    def vectors(x1,y1,z1,x2,y2,z2):
        vector1 = [x1, y1, z1]
        vector2 = [x2, y2, z2]
        Summation = [x1+x2, y1+y2, z1+z2]
        length = sqrt((x1-x2)**2+(y1-y2)**2+(z1-z2)**2)



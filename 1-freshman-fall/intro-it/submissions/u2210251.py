import math

number1 = int(input("Enter number x:\n "))
number2 = int(input("Enter number y:\n "))
expo = number1**number2
log = math.log(number1,2)
print("x**y = " + str(expo))
print("log(x) = " + str(log))
exit = input()
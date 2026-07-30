#Javohir Xatamov U2210251
# first assignment
print("This program will return the difference of the given number and 17, is it is less than 17" + "\n")
print("Or the double of their differnece if the given number is greater than 17" + "\n")
n = 15
if n <= 17:
    print (17 - n)
else :
    print (n - 17) * 2

#second assignment
print("This program will show whether the givent number is in the 100 range o 1000 or 2000 " + "\n")
n = 1100
isWithin = (( abs (1000 - n) <= 100) or ( abs (2000 - n) <= 100))
print ( isWithin )

#third assignment
print ("Numbers less than 237 from list will be shown below" + "\n")
numbers = [
386 , 462 , 47, 418 , 907 , 344 , 236 , 375 , 823 , 566 , 597 , 978 , 328 , 615 , 953 , 345 ,
399 , 162 , 758 , 219 , 918 , 237 , 412 , 566 , 826 , 248 , 866 , 950 , 626 , 949 , 687 , 217 ,
815 , 67, 104 , 58, 512 , 24, 892 , 894 , 767 , 553 , 81, 379 , 843 , 831 , 445 , 742 , 717 ,
958 ,743 , 527
]
for i in numbers:
    if i > 237:
        continue
    print(i)

#fourth assignment

print ("Welcome to GCD calculator" + "\n")
print ("Enter the first number:" + "\n")
x = int(input())
print ("Enter the second number: " + "\n")
y = int(input())
temp = 0
if y>x:
    temp = y
    y = x
    x = temp
while not y == 0:
    temp = y
    y = x%y
    x = temp
print ("GCM is " + str(x) + "\n")

#fifth assignment

print("Welcome to LCM calculator" + "\n")
print("Enter the first number" + "\n")
x = int(input())
print("Enter the second number" + "\n")
y = int(input())
orx = x
ory = y
temp = 0
GCD = 0
LCM = 0
if y>x:
    temp = y
    y = x
    x = temp
while not y == 0:
    temp = y
    y = x%y
    x = temp
GCD = x;
LCM = (orx * ory)/GCD
print("LCM is " + str(LCM) + "\n")
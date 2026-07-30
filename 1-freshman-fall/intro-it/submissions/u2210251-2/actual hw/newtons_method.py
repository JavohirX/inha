x = float(input())
i = 0 
y = 0
while(i>=0):
    if(abs((30 - y**3)) <= 0.0001):
        print("x :" + str(x) + "\n")
        print("i :" + str(i) + "\n")
        break
    y = x - ((x**3) - 30)/(3*(x**2))
    x = y
    i+=1

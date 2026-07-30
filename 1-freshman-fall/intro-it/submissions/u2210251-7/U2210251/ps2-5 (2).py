def listCounter(list1):
    k=0 
    for i in list1:
        temp = str(i)
        if len(temp)>1:
            for j in i:
                k+=j
            continue
        k+=i
    print(k)
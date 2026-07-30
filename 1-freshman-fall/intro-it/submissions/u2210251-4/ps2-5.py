n1 = {'a': 100, 'b': 200, 'c': 300}
n2 = {'a': 300, 'b': 200, 'd': 400}
for key in n2.keys():

    if key in n1.keys():

        n1[key] = n1.get(key) + n2.get(key)
    else:

        n1[key] = n2.get(key)
print(n1)

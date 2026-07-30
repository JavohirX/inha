random_list = [2,1,2,3,1,9]
frequency = {}
for item in random_list:
   if item in frequency:
      frequency[item] += 1
   else:
      frequency[item] = 1
print(frequency)
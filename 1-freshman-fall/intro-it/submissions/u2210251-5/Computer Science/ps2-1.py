word = input('Enter a word \n')
letter = input('Enter a letter to find\n')
j = 0
for i in word:
    if(i == letter):
        print(j);
        break
    j+=1
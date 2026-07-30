word = input('Enter your word \n')
isPalindrome = 'is palindrome'
i = 0
while(i<len(word)):
    if(word[i] != word[len(word) - (1+i)]):
        isPalindrome = 'is not palindrome'
        break
    i+=1
print('Word ' + isPalindrome)
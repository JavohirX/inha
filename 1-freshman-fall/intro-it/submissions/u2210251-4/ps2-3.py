import string
alphabet = list(string.lc)

def pangram(txt):

    isPangram = True
    if isPangram:

        for i in range(len(alphabet)):

            if alphabet[i] in txt:

                isPangram = True
            else:

                isPangram = False
    return f'isPangram: {isPangram}'
text = input().lower()
print(pangram(text))

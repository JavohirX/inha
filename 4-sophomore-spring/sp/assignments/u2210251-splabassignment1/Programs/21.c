#include <stdio.h>
#include<ctype.h>
int main() {
char snt[1000];
int characterCount = 0, alphabetCount = 0, numeralCount = 0, wordCount = 0;
int inWord = 0; // current word count

printf("Enter a sentence: ");
fgets(snt, sizeof(snt), stdin);

for (int i = 0; snt[i] != '\0'; ++i) {
if (snt[i] != ' ' && snt[i] != '\n') {
characterCount++;

if (isalpha(snt[i])) {
alphabetCount++;
}
else if (isdigit(snt[i])) {
numeralCount++;
}

if (!inWord) {
inWord = 1;
wordCount++;
}
} else {
inWord = 0;
}
}
// Print result
printf("\nResults:\n");
printf("Total Characters: %d\n", characterCount);
printf("Alphabets: %d\n", alphabetCount);
printf("Numerals: %d\n", numeralCount);
printf("Words: %d\n", wordCount);

return 0;
}

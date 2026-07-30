#include <stdio.h>

int main() {
char sentence[1000];

// Get the sentence
printf("Enter a sentence: ");
fgets(sentence, sizeof(sentence), stdin);

for (int i = 0; sentence[i] != '\0'; ++i) {
if (sentence[i] >= 'a' && sentence[i] <= 'z') {
// convet to uppercase
sentence[i] = sentence[i] - 'a' + 'A';
}
}

// print result
printf("Modified sentence: %s", sentence);

return 0;
}

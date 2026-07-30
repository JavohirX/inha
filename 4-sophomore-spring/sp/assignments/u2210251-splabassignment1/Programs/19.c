#include <stdio.h>

int main() {
char sentence[1000];
int i;

// Get sentence
printf("Enter your sentence: ");
fgets(sentence, sizeof(sentence), stdin);

// Go through the all characters
for (i = 0; sentence[i] != '\0'; i++) {
if (sentence[i] >= 'A' && sentence[i] <= 'Z') {
sentence[i] = sentence[i] + 32;
}
}

// Print resulted sentence
printf("Sentence with all lowercase letters: %s\n", sentence);

return 0;
}

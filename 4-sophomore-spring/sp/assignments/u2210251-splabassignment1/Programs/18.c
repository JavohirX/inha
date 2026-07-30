#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

int main() {
    int n;

    printf("Enter the value of n: ");
    scanf("%d", &n);

    char** names = (char**)malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        printf("Enter the name %d: ", i);
        names[i] = (char*)malloc(100 * sizeof(char)); 
        scanf("%s", names[i]);
    }

    qsort(names, n, sizeof(char*), compare);

    printf("\nNames in alphabetical order:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", names[i]);
    }

    for (int i = 0; i < n; i++) {
        free(names[i]);
    }
    free(names);

    return 0;
}

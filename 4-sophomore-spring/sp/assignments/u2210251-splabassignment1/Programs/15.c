#include <stdio.h>
#include <stdlib.h>

int main() {
    int size;

    printf("Enter the value of n: ");
    scanf("%d", &size);

    int *array = (int *)malloc(size * sizeof(int));


    for (int i = 0; i < size; i++) {
        printf("Enter the integer number %d: ", i);
        scanf("%d", &array[i]);
    }

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (array[i] < array[j]) {
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }

    printf("Result in decreasing order: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (array[i] > array[j]) {
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
    printf("Result in increasing order: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}

#include <stdio.h>

int main() {
    int n;
    float sum = 0, number;

    printf("Enter the value of n : ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter the real number %d: ", i);
        scanf("%f", &number);
        sum += number;
    }

    float average = sum / n;

    printf("\nSUM: %.2f\n", sum);
    printf("AVERAGE: %.2f\n", average);

    return 0;
}
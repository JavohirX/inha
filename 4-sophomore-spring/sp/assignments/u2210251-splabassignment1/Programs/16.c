#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int isPrime(int num) {
    if (num <= 1) return 0; 
    if (num <= 3) return 1; 
    if (num % 2 == 0 || num % 3 == 0) return 0; 

    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return 0; 
    }

    return 1; 
}

int main() {
    int n;

    printf("Enter the value of n: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));


    for (int i = 0; i < n; i++) {
        printf("Enter the element %d: ", i);
        scanf("%d", &arr[i]);
    }

    int positiveCount = 0, negativeCount = 0, oddCount = 0, evenCount = 0, primeCount = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) {
            positiveCount++;
        } else if (arr[i] < 0) {
            negativeCount++;
        }

        if (arr[i] % 2 == 0) {
            evenCount++;
        } else {
            oddCount++;
        }

        if (isPrime(abs(arr[i]))) {
            primeCount++;
        }
    }

    printf("\nPositive numbers: %d\n", positiveCount);
    printf("Negative numbers: %d\n", negativeCount);
    printf("Odd numbers: %d\n", oddCount);
    printf("Even numbers: %d\n", evenCount);
    printf("Prime numbers: %d\n", primeCount);

    return 0;
}

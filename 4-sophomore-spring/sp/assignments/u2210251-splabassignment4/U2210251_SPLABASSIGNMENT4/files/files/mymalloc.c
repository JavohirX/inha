#ifdef COMPILETIME
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

int counter = -1;
void* addresses[20];

void* myMalloc(size_t size) {
    void* ptr = malloc(size);
    counter++;
    addresses[counter] = ptr;
    printf("malloc(size: %d) at %p: \n", (int)size, ptr);
    return ptr;
}

void myFree(void *ptr) {
    for (int i = 0; i < counter + 1; i++) {
        if (addresses[i] == ptr) {
            addresses[i] = NULL;
        }
    }

    free(ptr);
}

void DetectAndFixLeaks() {
    int leaks_detected = 0;
    for (int i = 0; i < counter + 1; i++) {
        if (addresses[i] != NULL) {
            leaks_detected++;
            printf("\n\nDetected leak of memory at %p\n", addresses[i]);
            printf("Fixing memory leak: free(%p)\n\n", addresses[i]);
            free(addresses[i]);
            addresses[i] = NULL;
        }
    }
    if (!leaks_detected) {
        printf("No memory leaks detected\n");
    } else {
        printf("%d memory leaks detected and fixed\n", leaks_detected);
    }
}
#endif

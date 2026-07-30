#ifdef LINKTIME
#include <stdlib.h>
#include <stdio.h>

int counter = -1;
void* addresses[20];

void *__real_malloc(size_t size);
void __real_free(void *ptr);

void *__wrap_malloc(size_t size){
    void *ptr = __real_malloc(size);
    counter++;
    addresses[counter] = ptr;
    printf("malloc(size: %d) at %p: \n", (int)size, ptr);
    return ptr;
}

void __wrap_free(void *ptr){
    for (int i = 0; i < counter + 1; i++) {
            if (addresses[i] == ptr) {
                addresses[i] = NULL;
            }
    }
    __real_free(ptr);
}

#endif
#define malloc(size) myMalloc(size)
#define free(ptr) myFree(ptr)

void *myMalloc(size_t size);
void myFree(void *ptr);
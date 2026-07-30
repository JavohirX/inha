#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Global shared variable */
volatile long cnt = 0; /* Counter */

/* Thread routine */
void *thread(void *vargp)
{
    long niters = *((long *)vargp);  // Get the number of iterations
    long i;

    for (i = 0; i < niters; i++) {
        cnt++;  // Increment shared counter
    }
    return NULL;
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <niters> <nthreads>\n", argv[0]);
        exit(1);
    }

    long niters = atol(argv[1]);
    int nthreads = atoi(argv[2]);
    pthread_t tid[1000];  // Thread identifiers

    // Allocate space for niters copies to avoid shared access
    long *thread_niters = malloc(nthreads * sizeof(long));

    // Create threads
    for (int i = 0; i < nthreads; i++) {
        thread_niters[i] = niters;  // Each thread gets its own copy
        pthread_create(&tid[i], NULL, thread, &thread_niters[i]);
    }

    // Join threads
    for (int i = 0; i < nthreads; i++) {
        pthread_join(tid[i], NULL);
    }

    // Check result
    if (cnt != (nthreads * niters))
        printf("BOOM! cnt=%ld\n", cnt);
    else
        printf("OK cnt=%ld\n", cnt);

    printf("PRESS CTRL-C to terminate or CTRL-Z to suspend \n");
    pause();  // Wait for signal (CTRL-C or CTRL-Z)

    free(thread_niters);  // Free allocated memory
    exit(0);
}

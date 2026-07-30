#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread(void *vargp); 
char **ptr;  /* global var */

int main()
{
    long i;
    pthread_t tid[2];
    char *msgs[2] = {
        "Hello from foo",
        "Hello from bar"
    };

    printf("MAIN - PROGRAM:threadvshare.c LAB ASSIGNMENT5 Q7  SPRING 2024\n");
    printf("****************************************************************\n");

    ptr = msgs;
    for (i = 0; i < 2; i++)
    {
        pthread_create(&tid[i], NULL, thread, (void *)i);
        printf("Thread %ld with tid = %lu is created \n", i, tid[i]);
    }
    
    printf("****************************************************************\n");
    pthread_exit(NULL);
}

void *thread(void *vargp)
{
    long myid = (long)vargp;
    static int cnt = 0;
    printf("Now in thread %ld function \n", myid);
    printf("[%ld]:  %s (cnt=%d)\n", myid, ptr[myid], ++cnt);
    return NULL;
}


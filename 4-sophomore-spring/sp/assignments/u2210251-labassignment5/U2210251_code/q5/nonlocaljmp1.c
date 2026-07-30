#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <setjmp.h>

jmp_buf buf;

int error1 = 0;
int error2 = 1;

void foo(void), bar(void);

/* Deeply nested function foo */

void foo(void)
{
    printf("ENTERED function foo from main\n");
    if (error1)
	longjmp(buf, 1);
    bar();
}

void bar(void)
{
    	printf("ENTERED function bar from foo  \n");
	if (error2)
        longjmp(buf, 2);
}

int main()
{
    
	printf("MAIN - PROGRAM: nonlocaljmp1.c LAB ASSIGNMENT5 Q5  SPRING 2024\n");
   	printf("*****************************************************************\n");

    printf("ENTERED function main initially \n");
    switch(setjmp(buf)) {
    case 0:
        foo();
        break;
    case 1:
        printf("Detected an error1 condition in foo\n");
        break;
    case 2:
	printf("ENTERED function main from function bar directly \n");
        printf("Detected an error2 condition in function bar\n");
        break;
    default:
        printf("Unknown error condition in foo\n");
    }
   
    printf("*****************************************************************\n");
    exit(0);
}


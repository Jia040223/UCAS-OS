#include <stdio.h>
#include <syscall.h>
#include <unistd.h>
#include <sys/time.h>

#define REPEAT 100000000
int main() {
    struct timeval start, end;
    long long int time = 0;

    gettimeofday(&start, NULL);
    for (int i = 0; i < REPEAT; i++)
    {
        pid_t pid = getpid();
    }
    gettimeofday(&end, NULL);
    time =(long long)(end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);

    printf("*Using the library functions provided by glibc\n");
    printf("Time: %lld us\n\n", time);

    gettimeofday(&start, NULL);
    for (int i = 0; i < REPEAT; i++)
    {
        pid_t pid = syscall(SYS_getpid);
    }
    gettimeofday(&end, NULL);
    time =(long long)(end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);

    printf("**Using the syscall function\n");
    printf("Time: %lld us\n\n", time);

    gettimeofday(&start, NULL);
    for (int i = 0; i < REPEAT; i++)
    {
        pid_t pid;
        asm volatile (
            "movl $20, %%eax\n\t"
            "syscall\n\t"
            : "=a" (pid)
        );
    }
    gettimeofday(&end, NULL);
    time =(long long)(end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);

    printf("***Using the 'syscall' instruction\n");
    printf("Time: %lld us\n", time);

    return 0;
}

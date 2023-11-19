#include <stdio.h>
#include <time.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <unistd.h>

#define MAX_LOOP_NUM 1000000

int main(){
    struct timespec start;
    struct timespec end;
    long long timeuse1;
    long long timeuse2;
    long long timeuse3;
    pid_t pid;
    
    clock_gettime(CLOCK_MONOTONIC,&start);
    pid = getpid();
    clock_gettime(CLOCK_MONOTONIC,&end);
    timeuse1 = (end.tv_sec - start.tv_sec)*1e9+ end.tv_nsec - start.tv_nsec;
    
    clock_gettime(CLOCK_MONOTONIC,&start);
    pid = syscall(SYS_getpid);
    clock_gettime(CLOCK_MONOTONIC,&end);
    timeuse2 = (end.tv_sec - start.tv_sec)*1e9+ end.tv_nsec - start.tv_nsec;
    
    clock_gettime(CLOCK_MONOTONIC,&start);
    asm volatile (
            "movq   %[syscall_id], %%rax \n"
            "syscall \n"
            :
            : [syscall_id] "i" (SYS_getpid)
            : "rax"
        );
    clock_gettime(CLOCK_MONOTONIC,&end);
    timeuse3 = (end.tv_sec - start.tv_sec)*1e9+ end.tv_nsec - start.tv_nsec;

    printf("*Using the library functions provided by glibc\n");
    printf("Used Time: %lld ns\n", timeuse1);

    printf("**Using the syscall function\n");
    printf("Used Time: %lld ns\n", timeuse2);

    printf("***Using the 'syscall' instruction\n");
    printf("Used Time: %lld ns\n", timeuse3);


    return 0;
}
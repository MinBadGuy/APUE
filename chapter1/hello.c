#include "apue.h"

int main(void)
{
    printf("hello world from process ID %ld\n", (long)getpid());    // getpid返回进程ID，是个__pid_t类型，回溯后就是int
    exit(0);
}
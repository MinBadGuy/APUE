#include "apue.h"
#include <sys/wait.h>

int main(void)
{
    pid_t   pid;
    int     status;

    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid == 0)  // 子进程
    {
        exit(7);        // 正常终止
    }
    
    if (wait(&status) != pid)   // 等待子进程
    {
        err_sys("wait error");
    }
    pr_exit(status);    // 打印进程终止状态说明

    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid == 0)
    {
        abort();        // 产生信号：SIGABRT
    }

    if (wait(&status) != pid)
    {
        err_sys("wait error");
    }
    pr_exit(status);
    
    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid == 0)
    {
        status /= 0;    // 除以0产生信号：SIGFPE
    }
    
    if (wait(&status) != pid)
    {
        err_sys("wait error");
    }
    pr_exit(status);
    
    exit(0);
}
#include "apue.h"

int     globvar = 6;    // 全局变量，位于初始化数据段
char    buf[] = "a write to stdout\n";

int main(void)
{
    int     var;        // 自动变量，位于栈中
    pid_t   pid;

    var = 88;
    if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1)
    {
        err_sys("write error");
    }
    printf("before fork\n");

    if ((pid = fork()) == 0)    // 子进程
    {
        globvar++;
        var++;
    }
    else    // 父进程
    {
        sleep(2);
    }
    
    printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
    exit(0);
}
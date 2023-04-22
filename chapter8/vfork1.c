#include "apue.h"

int globvar = 6;

int main(void)
{
    int     var;
    pid_t   pid;

    var = 88;
    printf("before vfork\n");
    /*
        vfork创建的子进程在父进程的空间中运行，所以会改变父进程中的数据
        vfork保证子进程先执行，父进程后执行
    */
    if ((pid = vfork()) < 0)
    {
        err_sys("vfork error");
    }
    else if (pid == 0)  // 子进程
    {
        globvar++;
        var++;
        _exit(0);
    }
    
    printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
    exit(0);
}
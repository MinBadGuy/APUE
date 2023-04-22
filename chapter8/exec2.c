#include "apue.h"
#include <sys/wait.h>

int main(void)
{
    pid_t   pid;

    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid == 0)  // 子进程
    {
        // testinterp 是当前目录下的一个解释器文件
        if (execl("testinterp", "testinterp", "myarg1", "MY ARGS", (char *)0) < 0)
        {
            err_sys("execl error");
        }
    }
    
    if (waitpid(pid, NULL, 0) < 0)
    {
        err_sys("waitpid error");
    }
    
    exit(0);
}
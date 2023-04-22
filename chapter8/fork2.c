#include "apue.h"
#include <sys/wait.h>

int main(void)
{
    pid_t   pid;

    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid == 0)  // 子进程A
    {
        if ((pid = fork()) < 0)     // 子进程A又创建了它的子进程B
        {
            err_sys("fork error");
        }
        else if (pid > 0)   // 子进程A
        {
            exit(0);
        }
        
        // 子进程B
        sleep(2);
        printf("second child, parent pid = %ld\n", (long)getppid());
        exit(0);
    }
    
    if (waitpid(pid, NULL, 0) != pid)   // 等待子进程A
    {
        err_sys("waitpid error");
    }
    exit(0);
}
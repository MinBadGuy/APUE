#include "apue.h"

int main(void)
{
    pid_t   pid;

    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid != 0)  // 父进程
    {
        sleep(2);
        exit(2);
    }

    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid != 0)  // 第一个子进程
    {
        sleep(4);
        abort();
    }
    
    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid != 0)  // 第二个子进程
    {
        execl("/bin/dd", "dd", "if=/etc/passwd", "of=/dev/null", NULL);
        exit(7);
    }
    
    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid != 0)  // 第三个进程
    {
        sleep(8);
        exit(0);
    }
    
    sleep(6);           // 第四个进程
    kill(getpid(), SIGKILL);
    exit(6);
}
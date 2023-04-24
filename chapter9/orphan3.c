#include "apue.h"
#include <errno.h>

static void sig_hup(int signo)
{
    printf("SIGHUP received, pid = %ld\n", (long)getpid());
}

static void pr_ids(char *name)
{
    printf("%s: pid = %ld, ppid = %ld, pgrp = %ld, tpgrp = %ld\n",
        name, (long)getpid(), (long)getppid(), (long)getpgrp(), (long)tcgetpgrp(STDIN_FILENO));
    fflush(stdout);
}

int main(void)
{
    char    c;
    pid_t   pid;

    pr_ids("parent");
    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid > 0)   // parent
    {
        sleep(5);   // 睡眠, 让子进程先执行
    }
    else
    {
        pr_ids("child");
        signal(SIGHUP, sig_hup);    // 注册信号处理函数
        kill(getpid(), SIGTSTP);    // 给自己发送停止信号
        pr_ids("child");
        if (read(STDIN_FILENO, &c, 1) != 1)
        {
            printf("read error %d on controlling TTY\n", errno);
        }
        exit(0);
    }
    
    
    
}
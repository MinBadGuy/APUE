#include "apue.h"

volatile sig_atomic_t quitflag;

static void sig_int(int signo)
{
    if (signo == SIGINT)
    {
        printf("\ninterrupt\n");
    }
    else if (signo == SIGQUIT)
    {
        quitflag = 1;
    }
}

int main(void)
{
    sigset_t newmask, oldmask, zeromask;

    if (signal(SIGINT, sig_int) == SIG_ERR)
    {
        err_sys("signal(SIGINT) error");
    }
    if (signal(SIGQUIT, sig_int) == SIG_ERR)
    {
        err_sys("signal(SIGQUIT) error");
    }
    
    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);

    // 阻塞SIGINT信号，并保存当前信号屏蔽字
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
    {
        err_sys("SIG_BLOCK error");
    }

    while (quitflag == 0)
    {
        sigsuspend(&zeromask);
    }
    
    quitflag = 0;

    // 将信号屏蔽字恢复原值
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
    {
        err_sys("SIG_SETBLOCK error");
    }
    
    exit(0);
}
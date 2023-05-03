#include "apue.h"

static void sig_int(int);

int main(void)
{
    sigset_t newmask, oldmask, waitmask;

    pr_mask("program start: ");

    if (signal(SIGINT, sig_int) == SIG_ERR)
    {
        err_sys("signal(SIGINT) error");
    }
    sigemptyset(&waitmask);
    sigaddset(&waitmask, SIGUSR1);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGINT);

    // 阻塞SIGINT信号，并保存当前信号屏蔽字
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
    {
        err_sys("SIG_BLOCK error");
    }
    
    pr_mask("in critical region: ");

    if (sigsuspend(&waitmask) != -1)
    {
        err_sys("sigsuspend error");
    }
    
    pr_mask("after return from sigsuspend: ");

    // 将信号屏蔽字恢复原值
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
    {
        err_sys("SIG_SETMASK error");
    }
    
    pr_mask("program exit: ");

    exit(0);
}

static void sig_int(int signo)
{
    pr_mask("\nin sig_int: ");
}
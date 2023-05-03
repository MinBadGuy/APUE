#include "apue.h"

static void sig_quit(int);

int main(void)
{
    sigset_t newmask, oldmask, pendmask;

    if (signal(SIGQUIT, sig_quit) == SIG_ERR)
    {
        err_sys("can't caught SIGQUIT");
    }
    
    // 阻塞SIGQUIT并保存当前信号屏蔽字
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
    {
        err_sys("SIG_BLOCK error");
    }
    
    sleep(5);

    // 检查SIG_QUIT信号是否是未决的
    if (sigpending(&pendmask) < 0)
    {
        err_sys("sigpending error");
    }
    if (sigismember(&pendmask, SIGQUIT))
    {
        printf("\nSIGQUIT pending\n");
    }
    
    // 将信号屏蔽字恢复原状
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
    {
        err_sys("SIG_SETMASK error");
    }
    printf("SIGQUIT unblocked\n");

    sleep(5);
    exit(0);
}

static void sig_quit(int signo)
{
    printf("caught SIGQUIT\n");
    if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
    {
        err_sys("can't reset SIGQUIT");
    }
}
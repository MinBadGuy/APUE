#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void abort(void)
{
    sigset_t            mask;
    struct sigaction    action;

    /* 不能忽略SIGABRT信号，将其设为默认动作 */ 
    sigaction(SIGABRT, NULL, &action);
    if (action.sa_handler == SIG_IGN)
    {
        action.sa_handler = SIG_DFL;
        sigaction(SIGABRT, &action, NULL);
    }
    
    if (action.sa_handler == SIG_DFL)
    {
        /* 冲洗所有标准I/O流 */
        fflush(NULL);
    }
    
    /* 不能忽略SIGABRT信号，确保其是非阻塞的 */ 
    sigfillset(&mask);
    sigdelset(&mask, SIGABRT);
    sigprocmask(SIG_SETMASK, &mask, NULL);
    
    kill(getpid(), SIGABRT);

    fflush(NULL);
    action.sa_handler = SIG_DFL;
    sigaction(SIGABRT, &action, NULL);
    sigprocmask(SIG_SETMASK, &mask, NULL);
    kill(getpid(), SIGABRT);
    exit(1);
}
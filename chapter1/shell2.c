#include "apue.h"
#include <sys/wait.h>

static void sig_int(int);   // 信号处理函数

int main(void)
{
    char    buf[MAXLINE];
    pid_t   pid;
    int     status;

    if (signal(SIGINT, sig_int) == SIG_ERR)
    {
        err_sys("signal error");
    }
    
    printf("%% ");
    while (fgets(buf, MAXLINE, stdin) != NULL)  // 从标准输入读取一行
    {
        if (buf[strlen(buf) - 1] == '\n')   // fgets返回的每一行都以换行符终止，用null字节替换换行符
        {
            buf[strlen(buf) - 1] = 0;
        }

        if ((pid = fork()) < 0) // 创建子进程失败
        {
            err_sys("fork error");
        }
        else if (pid == 0)  // 子进程
        {
            execlp(buf, buf, (char *)0);    // 执行buf中给出的程序
            err_ret("couldn't execute: %s", buf);
            exit(127);
        }
        
        // 父进程
        if ((pid = waitpid(pid, &status, 0)) < 0)   // 等待子进程执行完毕
        {
            err_sys("waitpid error");
        }
        printf("%% ");
    }
    exit(0);
}

void sig_int(int signo)
{
    printf("interrupt\n%% ");
}
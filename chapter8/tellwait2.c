#include "apue.h"

static void charatatime(char *);

int main(void)
{
    pid_t   pid;

    TELL_WAIT();

    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid == 0)
    {
        WAIT_PARENT();      // 等待父进程执行完毕
        charatatime("output from child\n");
    }
    else
    {
        charatatime("output from parent\n");
        TELL_CHILD(pid);    // 通知子进程自己已经执行完毕
    }

    exit(0);    
}

static void charatatime(char *str)
{
    char *ptr;
    int c;

    setbuf(stdout, NULL);   // 将标准输出设置为不带缓冲的
    for (ptr = str; (c = *ptr++) != 0; )
    {
        fputc(c, stdout);
    }
    
}
#include "apue.h"
#include <errno.h>
#include <sys/time.h>

#if defined(MACOS)
#include <sys/syslimits.h>
#elif defined(SOLARIS)
#include <limits.h>
#elif defined(BSD)
#include <sys/param.h>
#endif

unsigned long long count;
struct timeval end;

void checktime(char *str)
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    if (tv.tv_sec >= end.tv_sec && tv.tv_usec >= end.tv_usec)
    {
        printf("%s count = %lld\n", str, count);
        exit(0);
    }
}

int main(int argc, char *argv[])
{
    pid_t   pid;
    char    *s;
    int     nzero, ret;
    int     adj = 0;

    setbuf(stdout, NULL);   // 将stdout设置成不带缓冲的
#if defined(NZERO)
    nzero = NZERO;          // NZERO是系统默认的友好值，20
#elif defined(_SC_NZERO)
    nzero = sysconf(_SC_NZERO);
#else
#error NZERO undefined
#endif
    printf("NZERO = %d\n", nzero);
    if (argc == 2)
    {
        adj = strtol(argv[1], NULL, 10);    // 将string转成long类型的整数，10表示按十进制来转
    }
    gettimeofday(&end, NULL);
    end.tv_sec += 10;   // 让每个进程运行10s，checktime函数会对时间做检查，如果达到10s就结束进程

    if ((pid = fork()) < 0)
    {
        err_sys("fork failed");
    }
    else if (pid == 0)  // 子进程
    {
        s = "child";
        printf("current nice value in child is %d, adjusting by %d\n", nice(0) + nzero, adj);
        errno = 0;  // 清除errno
        if ((ret = nice(adj)) == -1 && errno != 0)  // nice调用出错
        {
            err_sys("child set scheduling priority");
        }
        printf("now child nice value is %d\n", ret + nzero);
    }
    else    // 父进程
    {
        s = "parent";
        printf("current nice value in parent is %d\n", nice(0) + nzero);
    }
    
    for ( ; ; )
    {
        if (++count == 0)
        {
            err_quit("%s counter wrap", s);
        }
        // printf("%s count: %lld\n", s, count);
        checktime(s);
    }
}
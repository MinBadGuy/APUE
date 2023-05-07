#include "apue.h"
#include <pthread.h>

pthread_t ntid;

void printids(const char *s)
{
    pid_t       pid;
    pthread_t   tid;

    pid = getpid();         // 获取进程ID
    tid = pthread_self();   // 获取线程ID
    printf("%s pid %lu tid %lu (0x%lx)\n", s, (unsigned long)pid, (unsigned long)tid, (unsigned long)tid);
}

// 线程函数
void * thr_fn(void *arg)
{
    printids("new thread: ");
    return((void *)0);
}

int main(void)
{
    int err;
    err = pthread_create(&ntid, NULL, thr_fn, NULL);    // 创建线程
    if (err != 0)
    {
        err_exit(err, "can't create thread");
    }
    printids("main thread: ");
    sleep(1);
    exit(0);
}
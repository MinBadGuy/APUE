#include "apue.h"
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

extern int makethread(void * (*)(void *), void *);

struct to_info {
    void            (*to_fn)(void *);   /* function */
    void            *to_arg;            /* argument */
    struct timespec to_wait;            /* time to wait */
};

#define SECTONSEC 1000000000            /* seconds to nanoseconds */

#if !defined(CLOCK_REALTIME) || defined(BSD)
#define clock_nanosleep(ID, FL, REQ, REM)   nanosleep((REQ), (REM))
#endif

#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME 0
#define USECTONSEC 1000                 /* microseconds to nanoseconds */

void clock_gettime(int id, struct timespec *tsp)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    tsp->tv_sec = tv.tv_sec;
    tsp->tv_nsec = tv.tv_usec * USECTONSEC;
}
#endif

void * timeout_helper(void *arg)
{
    struct to_info  *tip;

    tip = (struct to_info *)arg;
    clock_nanosleep(CLOCK_REALTIME, 0, &tip->to_wait, NULL);    // sleep    ns
    (*tip->to_fn)(tip->to_arg);
    free(arg);
    return(0);
}

void timeout(const struct timespec *when, void (*func)(void *), void *arg)
{
    struct timespec now;
    struct to_info  *tip;
    int             err;

    clock_gettime(CLOCK_REALTIME, &now);    // 当前绝对时间
    if ((when->tv_sec > now.tv_sec) ||
        (when->tv_sec == now.tv_sec && when->tv_nsec > now.tv_nsec))    // 尚未达到超时时间
    {
        tip = malloc(sizeof(struct to_info));
        if (tip != NULL)
        {
            tip->to_fn = func;
            tip->to_arg = arg;
            tip->to_wait.tv_sec = when->tv_sec - now.tv_sec;
            if (when->tv_nsec >= now.tv_nsec)
            {
                tip->to_wait.tv_nsec = when->tv_nsec - now.tv_nsec;
            }  
            else {
                tip->to_wait.tv_sec--;
                tip->to_wait.tv_nsec = SECTONSEC - now.tv_nsec + when->tv_nsec;
            }
            err = makethread(timeout_helper, (void *)tip);  // 创建一个线程，超时时间到达时，执行相应的函数
            if (err == 0)
                return;
            else
                free(tip);
        }    
    }
    
    /**
     * 执行到此的条件：
     * (a) when <= now  已超时
     * (b) malloc 失败
     * (c) 无法创建线程
    */
    (*func)(arg);
}

pthread_mutexattr_t attr;
pthread_mutex_t     mutex;

void retry(void *arg)
{
    pthread_mutex_lock(&mutex);

    /* perform retry steps ... */

    pthread_mutex_unlock(&mutex);
}

int main(void)
{
    int             err, condition, arg;
    struct timespec when;

    if ((err = pthread_mutexattr_init(&attr)) != 0)                             // 初始化为默认属性
        err_exit(err, "pthread_mutexattr_init failed");
    if ((err = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE)) != 0) // 设置递归属性
        err_exit(err, "can't set recursive type");
    if ((err = pthread_mutex_init(&mutex, &attr)) != 0)                         // 用attr属性初始化mutex
        err_exit(err, "can't create recursive mutex");
    
    /* continue processing ... */

    pthread_mutex_lock(&mutex);

    if (condition)
    {
        // 计算当前绝对时间
        clock_gettime(CLOCK_REALTIME, &when);
        when.tv_sec += 10;  // 超时时间设置为10s后
        timeout(&when, retry, (void *)(unsigned long)arg);
    }
    pthread_mutex_unlock(&mutex);

    /* continute processing ... */

    exit(0);
}
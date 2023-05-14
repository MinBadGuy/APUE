#include "apue.h"
#include <pthread.h>

int makethread(void * (*fn)(void *), void * arg)
{
    int             err;
    pthread_t       tid;    // 线程ID
    pthread_attr_t  attr;   // 线程属性

    err = pthread_attr_init(&attr); // attr初始化成默认属性
    if (err != 0)
    {
        return(err);
    }
    
    err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);  // 设置分离状态属性
    if (err == 0)
    {
        pthread_create(&tid, &attr, fn, arg);
    }
    
    pthread_attr_destroy(&attr);    // 清理线程属性结构
    
    return(err);
}
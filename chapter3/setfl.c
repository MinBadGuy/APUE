#include "apue.h"
#include <fcntl.h>

void set_fl(int fd, int flags)
{
    int val;
    
    if ((val = fcntl(fd, F_GETFL, 0)) < 0)  // 获取文件当前状态标志
    {
        err_sys("fcntl F_GETFL error");
    }
    
    val |= flags;   // 或运算，将新增标志加入到val中

    if (fcntl(fd, F_SETFL, val) < 0)    // 设置文件描述符状态标志
    {
        err_sys("fcntl F_SETFL error");
    }
}
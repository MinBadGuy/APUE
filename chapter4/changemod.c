#include "apue.h"

int main(void)
{
    struct stat statbuf;

    if (stat("foo", &statbuf) < 0)  // 获取文件当前信息
    {
        err_sys("stat error for foo");
    }
    
    if (chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)   // 打开设置组ID、关闭组执行
    {
        err_sys("chmod error for foo");
    }
    
    if (chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0)    // 设置权限：rw-r--r--
    {
        err_sys("chmod error for bar");
    }
    
    exit(0);
}
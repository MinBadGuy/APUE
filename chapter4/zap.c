#include "apue.h"
#include <fcntl.h>

int main(int argc, char* argv[])
{
    int             i, fd;
    struct stat     statbuf;
    struct timespec times[2];
    for (i = 1; i < argc; i++)
    {
        if (stat(argv[i], &statbuf) < 0)    // 获取文件的当前信息
        {
            err_ret("%s: stat error", argv[i]);
            continue;
        }

        if ((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0) // truncate
        {
            err_ret("%s: open error", argv[i]);
            continue;
        }

        times[0] = statbuf.st_atim;     // 最后访问时间
        times[1] = statbuf.st_mtim;     // 最后修改时间
        if (futimens(fd, times) < 0)    // 重新设置时间
        {
            err_ret("%s: futimens error", argv[i]);
        }
        close(fd);
    }
    
    exit(0);
}
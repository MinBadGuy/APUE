#include "apue.h"

#define BUFFSIZE (4096)

int main(void)
{
    int     n;
    char    buf[BUFFSIZE];

    // read、write是不带缓冲的I/O
    // printf("%d\n", (n = -1) > 0);   // 0，先将-1赋值给n，再将n和0比较
    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) // 从标准输入读数据
    {
        if (write(STDOUT_FILENO, buf, n) != n)  // 往标准输出写数据
        {
            err_sys("write error");
        }
    }

    if (n < 0)
    {
        err_sys("read error");
    }
    
    exit(0);
}
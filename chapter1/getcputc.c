#include "apue.h"

int main(void)
{
    int c;

    // getc和putc属于标准I/O，带缓冲
    while ((c = getc(stdin)) != EOF)    // 从标准输入读取一个字符
    {
        if ((putc(c, stdout) == EOF))   // 将字符写入标准输出
        {
            err_sys("output error");
        }
    }

    if (ferror(stdin))
    {
        err_sys("input error");
    }
    
    exit(0);
}
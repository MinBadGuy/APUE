#include "apue.h"

int main(void)
{
    if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1) // 设置文件偏移量，返回新的文件偏移量，出错返回-1
    {
        printf("cannot seek\n");
    }
    else
    {
        printf("seek ok\n");
    }
    exit(0);
}
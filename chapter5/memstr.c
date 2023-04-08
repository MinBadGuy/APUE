#include "apue.h"

#define BSZ 48

int main()
{
    FILE    *fp;
    char    buf[BSZ];

    memset(buf, 'a', BSZ - 2);
    buf[BSZ - 2] = '\0';
    buf[BSZ - 1] = 'X';
    if ((fp = fmemopen(buf, BSZ, "w+")) == NULL)    // 创建内存流
    {
        err_sys("fmemopen failed");
    }
    printf("initial buffer contents: %s\n", buf);   // fmemopen在缓冲区开始处放置null字节
    fprintf(fp, "hello, world");                    // null字节追加到字符串结尾
    printf("before flush: %s\n", buf);
    fflush(fp);                                     // 流冲洗后缓存区才会变化
    printf("after fflush: %s\n", buf);              // hello, world
    printf("len of string in buf = %ld\n", (long)strlen(buf));  // 12

    memset(buf, 'b', BSZ - 2);
    buf[BSZ - 2] = '\0';
    buf[BSZ - 1] = 'X';
    fprintf(fp, "hello, world");
    fseek(fp, 0, SEEK_SET);                         // 将偏移量设置到起始处，引起缓冲区冲洗
    printf("after seek: %s\n", buf);                // bbbbbbbbbbbbhello, world
    printf("len of string in buf = %ld\n", (long)strlen(buf));  // 24

    memset(buf, 'c', BSZ - 2);
    buf[BSZ - 2] = '\0';
    buf[BSZ - 1] = 'X';
    fprintf(fp, "hello, world");
    fclose(fp);
    printf("after fclose: %s\n", buf);              // hello, worldcccccccccccccccccccccccccccccccccc
    printf("len of string in buf = %ld\n", (long)strlen(buf));  // 46

    return (0);
}
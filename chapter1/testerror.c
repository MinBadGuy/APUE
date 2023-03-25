#include "apue.h"
#include <errno.h>

int main(int argc, char* argv[])
{
    fprintf(stderr, "EACCES: %s\n", strerror(EACCES));  // strerror返回错误码对应的消息字符串
    errno = ENOENT;
    perror(argv[0]);    // 基于errno当前的值，返回一条出错消息
    exit(0);
}
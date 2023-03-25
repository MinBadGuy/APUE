#include "apue.h"
#include <dirent.h>

int main(int argc, char* argv[])
{
    DIR             *dp;    // 指向所打开目录流对象
    struct dirent   *dirp;  // readdi返回值类型，指向目录中的每一项

    if (argc != 2)
    {
        err_quit("usage: ls directory_name");
    }

    // printf("(dp = opendir(argv[1])): %ld\ndp: %ld\n",(dp = opendir(argv[1])), dp);
    // (dp = opendir(argv[1]))，即dp，是一个长整型整数，表示打开目录地址
    // 先将opendir的返回值赋给dp，然后将dp与NULL比较

    if ((dp = opendir(argv[1])) == NULL)    // 打开目录
    {
        err_quit("can't open %s", argv[1]);
    }

    while ((dirp = readdir(dp)) != NULL)    // 读取目录中的每一项
    {
        printf("%s\n", dirp->d_name);
    }
    
    closedir(dp);
    exit(0);
}
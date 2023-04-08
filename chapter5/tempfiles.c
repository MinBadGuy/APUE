#include "apue.h"

int main(void)
{
    char name[L_tmpnam], line[MAXLINE];
    FILE *fp;

    printf("%s\n", tmpnam(NULL));   // 创建临时文件
    
    tmpnam(name);                   
    printf("%s\n", name);

    if ((fp = tmpfile()) == NULL)   // 创建临时文件
    {
        err_sys("tmpfile error");
    }

    fputs("one line of output\n", fp);  // 向临时文件写内容
    rewind(fp);                         // 将流设置到文件起始位置

    if (fgets(line, sizeof(line), fp) == NULL)
    {
        err_sys("fgets error");
    }
    fputs(line, stdout);

    exit(0);
}
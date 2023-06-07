#include "apue.h"

int main(void)
{
    int     n;
    int     fd[2];
    pid_t   pid;
    char    line[MAXLINE];

    if (pipe(fd) < 0)
    {
        err_sys("pipe error");
    }
    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid > 0)   /* parent */
    {
        close(fd[0]);                       // 关闭管道的读端
        write(fd[1], "hello world\n", 12);  // 往管道写端写数据
    }
    else                /* child */
    {
        close(fd[1]);                       // 关闭管道的写端
        n = read(fd[0], line, MAXLINE);     // 从管道的读端读数据
        write(STDOUT_FILENO, line, n);      // 将读到的数据写到标准输出
    }

    exit(0);
}
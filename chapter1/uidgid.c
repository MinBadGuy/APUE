#include "apue.h"

int main(void)
{
    printf("uid = %d, gid = %d\n", getuid(), getgid()); // return user ID and group ID
    exit(0);
}
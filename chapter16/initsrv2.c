#include "apue.h"
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int initserver(int type, const struct sockaddr *addr, socklen_t alen, int qlen)
{
    char abuf[INET_ADDRSTRLEN];
    struct sockaddr_in  *sinp;
    sinp = (struct sockaddr_in *)addr;
    const char * paddr = inet_ntop(AF_INET, &sinp->sin_addr, abuf, INET_ADDRSTRLEN);
    printf("address: %s\n", paddr);
    printf("net port: %d\n", sinp->sin_port);           // 网络字节序   16796
    printf("host port: %d\n", ntohs(sinp->sin_port));   // 主机字节序   40001


    int fd, err;
    int reuse = 1;

    if ((fd = socket(addr->sa_family, type, 0)) < 0)
        return(-1);
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) < 0)   
        goto errout;
    if (bind(fd, addr, alen) < 0)
        goto errout;
    if (type == SOCK_STREAM || type == SOCK_SEQPACKET)
        if (listen(fd, qlen) < 0)
            goto errout;
    return(fd);

errout:
    err = errno;
    close(fd);
    errno = err;
    return(-1);
}
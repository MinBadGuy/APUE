#include "apue.h"
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAXSLEEP 128

int connect_retry(int domain, int type, int protocol, 
                  const struct sockaddr *addr, socklen_t alen)
{
    char abuf[INET_ADDRSTRLEN];
    struct sockaddr_in  *sinp;
    sinp = (struct sockaddr_in *)addr;
    const char * paddr = inet_ntop(AF_INET, &sinp->sin_addr, abuf, INET_ADDRSTRLEN);
    printf("address: %s\n", paddr);
    printf("net port: %d\n", sinp->sin_port);           // 网络字节序   16796
    printf("host port: %d\n", ntohs(sinp->sin_port));   // 主机字节序   40001

    int numsec, fd;
    /**
     * Try to connect with exponential backoff.
    */
    for (numsec = 1; numsec <= MAXSLEEP; numsec <<= 1)
    {
        if ((fd = socket(domain, type, protocol)) < 0)
            return(-1);
        if (connect(fd, addr, alen) == 0)
        {
            /**
             * Connection accepted.
            */
            return(fd);
        }
        close(fd);

        /**
         * Delay before trying again.
        */
        if (numsec <= MAXSLEEP)
            sleep(numsec);
    }
    return(-1);
}
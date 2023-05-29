#include <unistd.h>
#include <fcntl.h>

int lockfile(int fd)
{
    struct flock fl;
    
    fl.l_type = F_WRLCK;    // 独占性写锁
    fl.l_start = 0;
    fl.l_whence = SEEK_SET;
    fl.l_len = 0;
    return(fcntl(fd, F_SETLK, &fl));
}
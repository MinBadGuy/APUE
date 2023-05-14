#include <limits.h>
#include <string.h>

#define MAXSTRINGSZ 4096

static char envbuf[MAXSTRINGSZ];    // 静态存储器

extern char **environ;

/**
 * 不可重入
*/
char * getenv(const char *name)
{
    int i, len;

    len = strlen(name);
    for (i = 0; environ[i] != NULL; i++)
    {
        // 比较前n个字符
        if ((strncmp(name, environ[i], len) == 0) && (environ[i][len] == '='))
        {
            // 拷贝不多于（MAXSTRINGSZ-1）个字符至envbuf中
            strncpy(envbuf, &environ[i][len+1], MAXSTRINGSZ-1);
            return(envbuf);
        }
    }
    return(NULL);
}

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define _PATH_ "/tmp/file.tmp"
#define _SIZE_ 100
//写端
int main()
{
    umask(0);
    int ret = mkfifo(_PATH_, 0666 | S_IFIFO);
    if(ret == -1)
    {
        printf("mkfifo error\n");
        return 1;
    }
    int fd = open(_PATH_, O_WRONLY);
    if(fd < 0)
    {
        printf("open error!\n");
    }
    char buf[_SIZE_];
    memset(buf, '\0', sizeof(buf));
    while(1)
    {
        scanf("%s", buf);
        int ret = write(fd, buf, strlen(buf)+1);
        if(ret < 0)
        {
            printf("write error\n");
            break;
        }
        if(strncmp(buf, "quit", 4) == 0)
        {
            break;
        }
    }
    close(fd);
    return 0;
}

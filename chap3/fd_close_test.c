#include <apue.h>
#include<fcntl.h>


int main(int argc, char **argv)
{
    int err, fd1, fd2;

    fd1=open("fd_close.temp", O_RDWR|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR|S_IROTH);
    fd2=dup(fd1);

    if(write(fd1, "11", 2)==2)
        printf("fd1 write ok\n");
    else   
        printf("fd1 write error\n");
    close(fd1);
    printf("close fd1 ok\n");
    if(write(fd2, "22", 2)==2)
        printf("fd2 still available\n");
    else
        printf("fd2 write error\n");
        
    exit(0);
}
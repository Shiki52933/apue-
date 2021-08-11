#include "apue.h"
#include <fcntl.h>
#include <pthread.h>
#include <error.h>
#include <limits.h>
#include <semaphore.h>

#ifdef OPEN_MAX
static long openmax = OPEN_MAX;
#else 
static long openmax = 0;
#endif

#define OPEN_MAX_GUESS 256


sem_t t;

long open_max(void)  //get fd_max
{
    if(openmax == 0)
    {
        errno = 0;
        if((openmax=sysconf(_SC_OPEN_MAX))<0)
        {
            if(errno == 0)
                openmax = OPEN_MAX_GUESS;
            else
                err_sys("sysconf error");
        }
    }
    return openmax;
}

int my_dup2(int fd, int fd2)  //substitute dup2
{
    long openmax = open_max(); 

    if( fd<0 || fd>=openmax || fd2<0 ||fd2>=openmax)
    {    err_sys("Not Suitable fd");
        return -1;
    }

    if(fd==fd2)
        return fd2;

    sem_wait(&t);

    int *buf=(int *)malloc(4*openmax);
    long cnt=0;
    long curfd;

    close(fd2);
    while( (curfd=dup(fd)) != fd2)
        if(curfd==-1){
            sem_post(&t);
            free(buf);
            err_sys("dup error");
            return -1;
        }
        else{
            buf[cnt]=curfd;
            cnt++;
        }
    for(int i=0;i<cnt;i++)
        close(buf[i]);
    free(buf);

    sem_post(&t);
    return fd2;
}

int main(int argc, char** argv)
{
    // test my_dup2
    int fd=open("test.txt", O_RDWR|O_CREAT|O_APPEND, 0);
    char *test1="TEST STDOUT_FILENO\n";
    char *test2="TEST fd\n";

    sem_init(&t,0,1);
    my_dup2(fd, STDOUT_FILENO);
    write(STDOUT_FILENO, test1, strlen(test1));
    write(fd, test2, strlen(test2));
    _exit(0);
}
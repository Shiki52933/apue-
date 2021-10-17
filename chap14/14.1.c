#include "apue.h"
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>


char *filename = "14.1.txt";


int main(int argc, char *argv[])
{
    int fd;
    pid_t pid, firstchild;
    int index = 0;
    int maxindex = 100;
    char buf[14];
    int nread;
    struct flock flk;

    //initialize flcok flk
    flk.l_type = F_WRLCK;
    flk.l_whence = SEEK_SET;
    flk.l_start = 0;
    flk.l_len = 0;

    //open file and get write lock
    fd = open(filename, O_RDWR);
    if((fcntl(fd, F_SETLKW, &flk))==-1)
        err_quit("set write flock failed!\n");
    
    //fork 
    for(;index<maxindex; index++)
    {
        if(index == 0)
            if((pid=fork() )==0){
                // child 
                /* sleep(5); */
                if((fcntl(fd, F_SETLKW, &flk))==-1)
                    err_quit("child set write flock failed!\n");
                printf("child 0 get the write flock\n");
                printf("child 0 ready to exit\n");
                exit(0);
            }else
            {
                sleep(1);
                firstchild = pid;
            }
        else
            if((pid=fork() )==0){
                // child and get read flock
                flk.l_type = F_RDLCK;
                if((fcntl(fd, F_SETLKW, &flk))==-1)
                    err_quit("set read flock failed!\n");
                printf("child %d get read flock:\n", index);

                //I/O
                /* note that offset is shared! */
                lseek(fd, 0, SEEK_SET);
                if((nread=read(fd, buf, 14))>0){                    
                    write(STDOUT_FILENO, buf, nread);
                    write(STDOUT_FILENO, "\n", 1);
                }
                else
                    printf("no read!\n");
                exit(0);
            }else
                sleep(1);
    }
    //unlock and wait for the first child
    flk.l_type = F_UNLCK;
    if((fcntl(fd, F_SETLKW, &flk))==-1)
        err_quit("unlock write flock failed!\n");
    else
        printf("unlock write flock succeed!\n");
    waitpid(firstchild, NULL, 0);
    exit(0);
}

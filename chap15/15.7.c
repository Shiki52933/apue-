#include "apue.h"
#include <sys/select.h>
#include <unistd.h>

void pipe_select(int);

int main(int argc, char **argv)
{
    pipe_select(0);
    pipe_select(1);
}

void pipe_select(int idx){
    /* idx should be 0 or 1*/
    int fd[2], maxfd;
    fd_set wrfds, rdfds;


    if(pipe(fd) < 0)
        err_quit("pipe error\n");

    maxfd = max(fd[0], fd[1])+1;
    close(fd[idx]);

    FD_ZERO(&wrfds);
    FD_ZERO(&rdfds);

    if(idx==0)
        FD_SET(fd[1], &wrfds);
    if(idx==1)
        FD_SET(fd[0], &rdfds);

    if(select(maxfd, &rdfds, &wrfds, NULL, NULL)==-1)
        err_quit("select error");

    if(FD_ISSET(fd[1], &wrfds))
        printf("write end of pipe is usable\n");
    else
        printf("write end of pipe is not usable\n");
    if(FD_ISSET(fd[0], &rdfds))
        printf("read end of pipe is usable\n");
    else
        printf("read end of pipe is not usable\n");
}

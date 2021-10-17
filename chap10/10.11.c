#include <apue.h>
#include <sys/resource.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>

#define BUFFSIZE 100

void signal_myintr(int signo)
{
    printf("caught sigintr\n");
}

int main(int argc, char** argv)
{
    //set RLIMIT_FSIZE 1024
    struct rlimit rl;
    getrlimit(RLIMIT_FSIZE, &rl);
    if(rl.rlim_cur>1024)
        rl.rlim_cur=1024;
    setrlimit(RLIMIT_FSIZE, &rl);

    if(signal(SIGXFSZ, signal_myintr)==SIG_ERR)
        err_sys("signal error");

    int n,m;
    char buf[BUFFSIZE];

    while ((n=read(STDIN_FILENO, buf, BUFFSIZE))>0)
        if((m=write(STDOUT_FILENO, buf, n))!=n)
            err_sys("write error, write %d bytes", m);

    
    if(n<0)
        err_sys("read error");

    exit(0);
}


//sssssssssssssssssssssssssssssssssssssssssusels
//esssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss
//eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
//eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
//eeeeeeeeeeeeeeeeeeeeeeeeeeeeee
//eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
//eeeeeeeeeeeeeeeeeeeeeeeeeeeeee
//sssssssssssssssssssssssssssssssssssssssssusels
//esssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss
//eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
//eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
//eeeeeeeeeeeeeeeeeeeeeeeeeeeeee
//eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
//eeeeeeeeeeeeeeeeeeeeeeeeeeeeee

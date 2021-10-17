#include <apue.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>



int main(int argc, char** argv)
{
    char c;
    pid_t pid, s_pid;
    char leader[]="leader right\n";
    char term[]="no control terminal\n";
    int flag;
    
    if((pid=fork())<0){
       err_sys("fork errno\n");
    }else if (pid == 0){
        if((s_pid=setsid())==-1)
        	err_sys("setsid error\n");
        if(getpid()==getpgid(0))
        	write(STDOUT_FILENO, leader, strlen(leader));
        else
        	write(STDOUT_FILENO, "leader wrong\n", strlen(leader));
        if((flag=open("/dev/tty", O_RDWR|O_NOCTTY))==-1)
        	write(STDOUT_FILENO, term, strlen(term));
        else
        	write(STDOUT_FILENO, " A Control terminal\n", strlen(term));
        }
        
     exit(0);
   
}

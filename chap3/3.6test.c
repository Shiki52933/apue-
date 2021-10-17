#include<apue.h>
#include<unistd.h>
#include<fcntl.h>
#include<error.h>

char *init="This is the initial txt fiel\n";
char *upda="This is the updated txt file\n";
char *path="3.6.txt";

int test_init(void)
{
    int fd=open(path, O_RDWR | O_CREAT |O_TRUNC, 0);
    if(fd==-1)
        return -1;
    int val = write(fd, init, strlen(init));
    close(fd);
    return val;
}

int main(int argc, char** argv)
{
           
    int fd=open(path, O_RDWR|O_APPEND, 0);  //initial and open file

    lseek(fd, 0, SEEK_SET);
    char buf[strlen(init)+1];
    buf[strlen(init)]=0;
    read(fd, buf, strlen(init));
    write(STDOUT_FILENO, buf, strlen(init));
    printf(" use lseek to just read from 0\n");  //read from 0

    lseek(fd, 0, SEEK_SET);
    int try=write(fd, upda, strlen(upda));
    printf("%d\n",try);
    if(try>0){
        printf("write error\n");
        int try=write(fd, upda, strlen(upda));
        printf("write %d\n", try);
    }
    read(fd, buf, strlen(init));
    write(STDOUT_FILENO, buf, strlen(init));
    printf(" after update, read from 0\n");   //update and read

    close(fd);
}
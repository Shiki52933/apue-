#include<sys/select.h>
#include"apue.h"

int main(int argc, char **argv)
{
    printf("sizeof(fd_set) is %ld \n",sizeof(fd_set));
}
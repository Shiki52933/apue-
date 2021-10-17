#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/syscall.h>

void *thread(void *p);
pid_t gettid();

int main(int argc, char **argv)
{
    pthread_t t1,t2;
    pthread_create(&t1, NULL, thread, NULL);
    pthread_create(&t2, NULL, thread, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    _exit(0);
}

void *thread(void *p)
{
    for(int i=0;i<100;i++)
        printf("this is %ld\n", (long)gettid());
}

pid_t gettid()
{
    return syscall(SYS_gettid);
}
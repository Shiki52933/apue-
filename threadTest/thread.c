#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t s;
int cnt = 0;

void *thread(void *p);

int main(int argc, char **argv)
{
    pthread_t t1,t2;
    int num=10000;

    pthread_create(&t1, NULL, thread, &num);
    pthread_create(&t2, NULL, thread, &num);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    if(cnt != (2*num))
        printf("error: bad thread order\n");
    else
        printf("correct: good thread order\n");

    _exit(0);
}

void *thread(void *p)
{
    int i=*((int*)p);
    for(int j=0;j<i;j++)
        cnt+=1;
    return NULL;
}

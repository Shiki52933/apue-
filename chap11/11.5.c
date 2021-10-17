#include <apue.h>
#include <pthread.h>

typedef struct 
{
    pthread_cond_t cond;
    pthread_mutex_t mutex;
    unsigned long long count;
}my_pthread_barrier_t;

my_pthread_barrier_t barrier;
int arr[100];

int my_pthread_barrier_init(my_pthread_barrier_t *barrier, unsigned long long count)
{
    if(barrier!=NULL && count>0){
        pthread_cond_init(&barrier->cond, NULL);
        pthread_mutex_init(&barrier->mutex, NULL);
        barrier->count=count;
        return 0;
    }
    return 1;
}

int my_pthread_barrier_wait(my_pthread_barrier_t *barrier)
{
    pthread_mutex_lock(&barrier->mutex);
    if(barrier->count <= 1){      
        if(barrier->count == 1)
            barrier->count=0;
        pthread_cond_broadcast(&barrier->cond);
        pthread_mutex_unlock(&barrier->mutex);
        return 0;
    }
    barrier->count -= 1;
    pthread_cond_wait(&barrier->cond, &barrier->mutex);
    pthread_mutex_unlock(&barrier->mutex);
    return 0;
}

void *th_fun(void *p)
{
    int i=(int)(long long )p;
    arr[i]=1;
    my_pthread_barrier_wait(&barrier);
}



int main(int argc, char** argv)
{
    int i,count;

    my_pthread_barrier_init(&barrier, 101);
    for(int j=0;j<100;j++)
    {
        pthread_t tid;
        pthread_create(&tid, NULL, th_fun, (void *)(long)j);
    }

    my_pthread_barrier_wait(&barrier);

    for(i=0,count=0;i<100;i++)
    {
        printf("arr[%d]= %d\n", i, arr[i]);
    }
}

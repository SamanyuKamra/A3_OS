#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>



pthread_mutex_t waiter;     //Waiter is created for passing on the forks
sem_t forks[5];             //Global Declaration

void eat(int philosphers)
{
    printf("Philospher %d eating with fork %d and %d\n",philosphers,philosphers,(philosphers +1)%5);
    usleep(500000);
    sem_post(&forks[philosphers]);
    sem_post(&forks[(philosphers + 1)%5]);
}

void getforks(int philosphers){
    sem_wait(&forks[philosphers]);
    sem_wait(&forks[(philosphers + 1)%5]);
}

void *philospherThinking(void *i)
{
    int philosphers = *((int *)i);
    while(1)
    {
        pthread_mutex_lock(&waiter);
        getforks(philosphers);
        pthread_mutex_unlock(&waiter);
        eat(philosphers);
    }
}
int main()
{
    pthread_t DP[5];
    int i[5] = {0,1,2,3,4};
    pthread_mutex_init(&waiter, NULL); //initialized forks
    int j = 0;
    while(j<5){
        sem_init(&forks[j],0,1);
        j++;
        
    }
    
    // creating philosphers
    for(int k = 0; k<5; k++){
        if(pthread_create(&DP[k],NULL,philospherThinking,&i[k]) == -1)
        {
            printf("Error in threads creation\n");
        }
    }
    int x = 0;
    while(x<5){
        pthread_join(DP[x],NULL);    
        x++;
    }
    
       
    
    return 0;
}

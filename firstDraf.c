#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>


#define N 5
enum states {THINKING, HUNGRY, EATING} state[N];

void * philosopher(void *num);
void pick_up(int);
void put_down(int);
void test(int);

int phil_num[N]={0,1,2,3,4};


void *philosopher(void *num)
{
    while(1)
    {
        int *i = num;
        pick_up(*i);
        put_down(*i);
    }
}

void pick_up(int mynum)
{
    sem_wait(&mutex);
    state[mynum] = HUNGRY;
    printf("Philosopher %d gives thinking a rest because she is HUNGRY\n",mynum+1);
    test(mynum);
    sem_post(&mutex);
   
}



void put_down(int mynum)
{
    sem_wait(&mutex);
    state[mynum] = THINKING;
    printf("Philosopher %d is putting down fork\n" ,mynum+1);
    printf("Philosopher %d is THINKING about universe\n",mynum+1);
    test((mynum+4) % N);
    test((mynum+1) % N);
    sem_post(&mutex);
    sleep(2);
}


void test(int mynum)
{
    if (state[(mynum+4) % N] != EATING && state[mynum] == HUNGRY &&  state[(mynum+1) % N] != EATING)
    {
    state[mynum] = EATING;
    printf("Philosopher %d is picking up fork\n",mynum+1);
    printf("Philosopher %d is EATING\n",mynum+1);
    }
}



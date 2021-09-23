/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <pthread.h>
int fuel=0;
pthread_mutex_t mutex;
pthread_cond_t condFuel;
void* car_consuming(){
    pthread_mutex_lock(&mutex);
    while(fuel<40){
        printf("No fuel:%d\n",fuel);
        // sleep(1);
        pthread_cond_wait(&condFuel,&mutex);
        /*Equivalent to 
        1) pthread_mutex_unlock(&mutex);
        2) Wait for signal on condFuel
        3) Upon acquiring the signal, pthread_mutex_lock(&mutex)
        
        */
    }
    fuel-=40;
    printf("Fuel left after consuming 40 litres:%d\n",fuel);
    
    pthread_mutex_unlock(&mutex);
}

void* fuel_filling(){
    for(int i=0; i <5;i++){
    pthread_mutex_lock(&mutex);
        fuel+=60;
    printf("Fuel after filling:%d\n",fuel);
    pthread_mutex_unlock(&mutex);
    pthread_cond_broadcast(&condFuel);//--Note: This is outside the mutex
    sleep(1);
    }
}

int main()
{
pthread_t t[5];
pthread_mutex_init(&mutex,NULL);
pthread_cond_init(&condFuel,NULL);
for (int i=0; i<5;i++){
    if(i==4){
        if(pthread_create(t+i,NULL,&fuel_filling,NULL)!=0)
            perror("Error creating thread");
    }
    else
    {
        if(pthread_create(t+i,NULL,&car_consuming,NULL)!=0)
            perror("Error creating thread");
    }
}
for (int i=0; i<5;i++){
    if(i==4){
        if(pthread_join(*(t+i),NULL)!=0)
            perror("Error joining thread");
    }
    else
    {
        if(pthread_join(*(t+i),NULL)!=0)
            perror("Error joining thread");
    }
}

pthread_mutex_destroy(&mutex);
pthread_cond_destroy(&condFuel);
    return 0;
}

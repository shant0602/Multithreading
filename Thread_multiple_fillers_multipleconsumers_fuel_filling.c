/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
int fuel=0;
// typedef enum{
//     false,
//     true
// } bool;
/*
if max_cars_limit is  a numbe which is not possible to be filled by given number of fuel dumps
then the threads are stuck forever in the while(cars_refueled<max_cars_limit), so we need something as timeout
*/
static int isFilling=0;
int i=0,cars_refueled=0,max_cars_limit=13;
pthread_mutex_t mutex;
pthread_cond_t carRefuel;
pthread_cond_t fillFuel;


void* car_consuming(){
    while(cars_refueled<max_cars_limit){
    // printf("cars_refueled=%d-----thread_ID=%zu\n",cars_refueled,pthread_self());  
    pthread_mutex_lock(&mutex);
    while(isFilling==-1)
        pthread_cond_wait(&carRefuel,&mutex);
    ++isFilling;
    //car consuming
    //!!!!!!break condition will eventually cause a problem thats why used second if!!!!!!
    // if(cars_refueled >=8){
    //     pthread_mutex_unlock(&mutex);//If we dont release it in this case the thread gets locked forever
    // //   return 0;//---hangs even after unlocking
    //   break;
    // }
    if(cars_refueled<max_cars_limit){
    if(fuel>=40){
        fuel-=40;
        ++cars_refueled;
        ++i;
        printf("Fuel left after consuming 40 litres:%d--%d     cars_refueled=%d, thread_ID=%zu \n",fuel,i,cars_refueled,pthread_self());
    }
    else
    {
        ++i;
        // printf("Insufficient Fuel left:%d--%d\n",fuel,i);
    }
    }
    // pthread_mutex_unlock(&mutex);
        // sleep(1);
    // pthread_mutex_lock(&mutex);
    --isFilling;
    if(isFilling==0)
        pthread_cond_broadcast(&fillFuel);
    pthread_mutex_unlock(&mutex);
    }
    printf("About to exit\n");
}

void* fuel_filling(){
    
    pthread_mutex_lock(&mutex);
    while(isFilling!=0)
        pthread_cond_wait(&fillFuel,&mutex);
    isFilling=-1;
    pthread_mutex_unlock(&mutex);
    //Filling
    fuel+=60;
    ++i;
    printf("Filling fuel:%d--%d\n",fuel,i);

    pthread_mutex_lock(&mutex);
    isFilling=0;
    pthread_mutex_unlock(&mutex);
    
    pthread_cond_broadcast(&carRefuel);//--Note: This is outside the mutex
    pthread_cond_broadcast(&fillFuel);//--Note: This is outside the mutex

    // sleep(1);

}

int main()
{
pthread_t t[50];
pthread_mutex_init(&mutex,NULL);
pthread_cond_init(&carRefuel,NULL);
pthread_cond_init(&fillFuel,NULL);
for (int i=0; i<50;i++){
    if(i%5==0){
        if(pthread_create(&t[i],NULL,fuel_filling,NULL)!=0){}
            // perror("Error creating thread");
    }
    else
    {
        if(pthread_create(&t[i],NULL,&car_consuming,NULL)!=0){}
            // perror("Error creating thread");
    }
}
for (int i=0; i<50;i++){
        if(pthread_join(t[i],NULL)!=0)
            perror("Error joining thread");
}
printf("Reached end");
pthread_mutex_destroy(&mutex);
pthread_cond_destroy(&carRefuel);
pthread_cond_destroy(&fillFuel);

    return 0;
}

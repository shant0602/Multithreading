/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <pthread.h>
int var[10]={1,2,3,4,5,6,7,8,9,10};
int sum=0;
pthread_mutex_t mutex;
void message(void* value){
    // printf("Hello Shantanu%d\n",getpid());
    int* local_val=(int*)value;
    pthread_mutex_lock(&mutex);
    int l=5*(*local_val-1);
    int u=5*(*local_val);
    for(int i=l;i<u;i++)
    sum+=var[i];
        // for (int i=0; i <1000000;i++){
        // *local_val=(*local_val)+1;
        // var+=1;
    // }
    // var*=*local_val;
    printf("%d\n",*local_val);
    pthread_mutex_unlock(&mutex);
    free(local_val);

}

int main()
{
    pthread_mutex_init(&mutex,NULL);
    pthread_t t[2];

    for (int i=1; i <=2;i++){
        int* a=malloc(sizeof(int));
        *a=i;
        if(pthread_create((t+i-1),NULL,&message,a)!=0){
            perror("Failed create");
        }
    }
    for (int i=0; i <2;i++){
        if(pthread_join(*(t+i),NULL)!=0)
            perror("failed join");
    }
    printf("The value of sum =%d",sum);
    pthread_mutex_destroy(&mutex);
    return 0;
}
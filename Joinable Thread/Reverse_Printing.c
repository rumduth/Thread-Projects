#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> //For working with POSIX thread
#include <unistd.h>
#include <errno.h>

void* func_callback(void* arg){
    int n = *(int*)arg;
    printf("Number: %d\n",n);
    free(arg);
    return NULL;
}

void thread_creation(pthread_t* thread, int id){
    int* _id = calloc(1,sizeof(int));
    *_id = id;
    pthread_attr_t attr; //This variable set the property of thread which we are creating
    pthread_attr_init(&attr); //Initlialize the attribute thread
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE); // set the thread is created joiable;
    pthread_create(thread,&attr,func_callback,(void*)_id);
}

int main(){
    int n = 0;
    printf("Enter number: ");
    scanf("%d",&n);
    void* result;
    pthread_t threads[n]; 
    for(int thread_id = n-1; thread_id >= 0; thread_id--){
        thread_creation(&threads[thread_id],thread_id + 1);
    }
    for(int thread_id = n-1; thread_id >= 0; thread_id--){
        pthread_join(threads[thread_id],&result);
    }

    return 0;
}
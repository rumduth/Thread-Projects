#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> //For working with POSIX thread
#include <unistd.h>
#include <errno.h>


//For example, we - thread 1 have two apple, we go to thread 2 to borrow juice grinder to make apple juice, but 
//after making the juice, thread 2 will drink it, not thread1
void * publisher(void* args){
    int a;
    int b;
    
    
}


int main(){
    pthread_t thread1;
    pthread_t thread2;

    pthread_create(&thread1, NULL,publisher,NULL);
    pthread_create(&thread2, NULL,subscriber,NULL);





}
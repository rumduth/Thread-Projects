#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> //For working with POSIX thread
#include <unistd.h>

static void * thread_fn_callback(void *arg){
    char* input = (char*) arg;
    int a = 0;
    while(a < 10){
        printf("input string = %s\n",input);
        sleep(1);
        if(a == 5)
            pthread_exit(0);
        a++;
    }
    return NULL;
}

void thread1_create(){
    pthread_t pthread1; //thread handle

    static char *thread_input1 = "I am thread no 1";
    int rc = pthread_create(&pthread1,NULL,thread_fn_callback,(void*)thread_input1);
    if(rc != 0){ //Fail creation
        printf("Erro occurred, thread could not be created, errno = %d\n",rc);
        exit(0);
    }
}


int main(int argc, char** arv){
    thread1_create();
    printf("main fn paused\n");
    pause();
    return 0;
}
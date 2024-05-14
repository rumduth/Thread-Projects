#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> //For working with POSIX thread
#include <unistd.h>
#include <errno.h>
#include <string.h>
/*
There are maybe more beautiful ways, 
However I prefer working in general way, when we don't know the number of lines in a text file
So I will count the number of line first, and then divide the task for each thread.
Of course, if we know how many lines of the text file in advance, we can do it easier without reading the textfile two times
*/
void * func_callback(void* arg){
    char* str = (char*)arg;
    int length = strlen(str);
    int numberWords = 0;
    for(int i = 0; i < length; i++){
        if(str[i] == ' ')
            numberWords++;
    }
    free(arg);
    int* result = calloc(1,sizeof(int));
    *result = numberWords + 1;
    return (void *)result;
    
}


void create_thread(pthread_t* thread, char* str){
    pthread_attr_t attr; //This variable set the property of thread which we are creating
    pthread_attr_init(&attr); //Initlialize the attribute thread
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE); // set the thread is created joiable;
    pthread_create(thread,&attr,func_callback,(void*)str);
}



int main(){
    FILE* file;
    char filename[100];
    int numberThreads = 0;
    int count = 0;
    char c;
    printf("Enter the filename: ");
    scanf("%s",filename);
    printf("Enter number of threads: ");
    scanf("%d",&numberThreads);
    
    //Open the file
    file = fopen(filename,"r");
    if(file == NULL){
        printf("Could not open file %s\n",filename);
        return 1;
    }

    //Count lines
    while((c = fgetc(file)) != EOF){
        if(c == '\n')
            count++;
    }
    printf("Number of lines: %d\n",count);

    int checkPoints[numberThreads]; //To save the point that signal each thread works on each parts
    for(int i = 0; i < numberThreads; i++){
        checkPoints[i] = count/numberThreads * i;
    }

    pthread_t threads[numberThreads];
    fseek(file, 0, SEEK_SET);//Returning the file reading pointer to the beginning of the file;


    int line = 0;
    for(int i = 0; i < numberThreads; i++){
        int end = 0;
        if(i == numberThreads - 1){
            printf("Thread %d works from the line %d to %d\n", i + 1, checkPoints[i]+1, count);
            end = count;
        }else{
            printf("Thread %d works from the line %d to %d\n", i + 1, checkPoints[i]+1, checkPoints[i+1]);
            end = checkPoints[i+1];
        }

        char *str = (char*) malloc(1 * sizeof(char));
        int length = 0;
        while(line <= end){
            char c = fgetc(file);
            str = (char *)realloc(str, (length + 2) * sizeof(char)); // +2 for the new character and null terminator
            str[length] = c;
            length++;
            if(c == '\n' || c == EOF)
                line++;
        }
        str[length] = '\0'; // Null-terminate the string
        create_thread(&threads[i],str);
    }
    int totalWords = 0;
    void * words;


    for(int i = 0; i < numberThreads; i++){
        printf("The main thread is waiting the number of words from thread %d\n", i + 1);
        pthread_join(threads[i],&words);
        printf("Thread %d has %d words\n", i + 1, *(int*)words);
        totalWords += *(int*)words;
        free(words);
        words = NULL;
    }

    printf("Total words in file %s is %d, working with %d\n",filename,totalWords,numberThreads);
    fclose(file);
    return 0;
}
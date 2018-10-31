//
//  wc_thread.c
//  
//  This program demonstrates the use of the work crew model 
//  of threading.
//  
//  All threads that are needed for the program to operate
//  are created at the start of the process. When all the
//  threads complete their tasks, the resources from the
//  threads will be collected by the main process and 
//  the program will output the result.
//  
//  This program serves only to illustrate the work crew
//  model of threading, so its only task is to 
//  print the names of all the input files with the characters
//  " thread" attached at the end of each file name.
//  
//  When given multiple input files, each of those task is 
//  completed in a thread.
//
//  How to use: 
//  gcc –o multithread.c –lpthread
//  ./a.out f1.txt f2.txt f3.txt f4.txt ...
//

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <pthread.h>
#include <string.h>


void *thread(void *vargp);

int main(int argc, char * argv[]) 
{ 
    int i; 
    pthread_t * tid = malloc((argc - 1) * sizeof(pthread_t));   // multiple threads id
    char *output[argc - 1]; // store all output from all threads
    
    // create the threads and pass all cmd argument names as arguments
    for (i = 1; i < argc; i++)
    {
        pthread_create(&tid[i - 1], NULL, thread, argv[i]);
    }

    wait(NULL);
    // gather the returned data from all the threads
    for (i = 1; i < argc; i++)
    {
        output[i - 1] = malloc(200);
        pthread_join(tid[i - 1], (void *)&output[i - 1]);
    }

    for (i = 0; i < argc - 1; i++)
    {
        printf("%s\n", output[i]);
    }

    pthread_exit(NULL); 
    return 0; 
} 

/*
    This function adds " thread"
    at the end of each file name.
*/
void *thread(void *vargp) 
{
    // pthread argument
    char *file_name = (char *)vargp;

    // pthread argument cannot be modified
    // dump the data in a different string
    // then make changes to that one instead.
    char *file_mod = malloc(sizeof(file_name) + 8);
    strcpy(file_mod, file_name);
    strcat(file_mod, " thread\0");

    pthread_exit((void *)file_mod);
} 

/* Includes */
#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */ 
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <stdlib.h>     /* General Utilities */
#include <pthread.h>    /* POSIX Threads */
#include <string.h>     /* String handling */
#include <semaphore.h>  /* Semaphore */
#include "printerror.h"

#define NUMTHREADS  8
#define NUMADMITTED 6
/* global vars */
/* semaphores are declared global so they can be accessed 
   in main() and in thread routine,
   here, the semaphore is used as a mutex+condvar */
sem_t sem;
int counter; /* shared variable */

void *ThreadFunction ( void *ptr )
{
    int x, rc; 
    x = *((int *) ptr);
    printf("Thread %d: Waiting to enter critical region...\n", x);
    fflush(stdout);
    rc=sem_wait(&sem);       /* down semaphore */
    if( rc != 0 ) PrintErrnoAndExit( "sem_wait");
    /* START CRITICAL REGION */
    printf("Thread %d: Now in critical region...  sleeping \n", x);
    fflush(stdout);
    sleep(1);
    counter++;
    /* END CRITICAL REGION */    
    rc = sem_post(&sem);       /* up semaphore */
    if( rc != 0 ) PrintErrnoAndExit( "sem_post");

    printf("Thread %d leave critical region...\n", x);
    fflush(stdout);
    
    pthread_exit(NULL); /* exit thread */
}

int main()
{
    int i[NUMTHREADS], rc, j;
    pthread_t thread[NUMTHREADS];
   
    /* argument to threads */
    for(j=0;j<NUMTHREADS;j++)  i[j]=j; 
    
    /* rc =sem_init(&sem, 0, 1); initialize sem to 1 - binary semaphore */
    /* initialize sem to NUMADMITTED - n-ary semaphore */
    rc =sem_init(&sem, 0, NUMADMITTED);
                                /* second param = 0 - semaphore is local */
    if( rc != 0 ) PrintErrnoAndExit( "sem_init");
                                 
    /* Note: you can check if thread has been successfully created by checking return value of
       pthread_create */                                 
    for(j=0;j<NUMTHREADS;j++) {
        rc = pthread_create (&thread[j], NULL, ThreadFunction, (void *) &i[j]);
        if( rc != 0 ) PrintErrnoAndExit( "pthread_create");
    }
    
    for(j=0;j<NUMTHREADS;j++) {
        rc = pthread_join(thread[j], NULL);
        if( rc != 0 ) PrintErrnoAndExit( "pthread_join");
    }

    rc = sem_destroy(&sem); /* destroy semaphore */
    if( rc != 0 ) PrintErrnoAndExit( "sem_destroy");
                  
    /* exit */  
    exit(0);
} /* main() */




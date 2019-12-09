/* file:  CondVarSignal.c 
   Routine che fornisce un synchronization point. 
   E' chiamata da ognuno dei SYNC_MAX pthread, che si fermano 
   finche' tutti gli altri sono arrivati allo stesso punto di esecuzione. 
*/ 

/* simboli già messi nella riga di comando del compilatore 
#define _THREAD_SAFE
#define _REENTRANT
#define _POSIX_C_SOURCE 200112L
*/

#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h> 
#include "printerror.h"

#define SYNC_MAX 5 

pthread_mutex_t sync_lock = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t sync_cond[SYNC_MAX] = {PTHREAD_COND_INITIALIZER}; 
int sync_count = 0; 

void SyncPoint(void) { 
	int rc;
    int next;
	/* blocca l'accesso al counter */ 
	rc = pthread_mutex_lock(&sync_lock); 
	if(rc) PrintERROR_andExit(rc,"pthread_mutex_lock failed"); /* no EINTR */

    
	/* incrementa il counter di quelli arrivati*/ 
	sync_count++; 
    next=sync_count;

    if(sync_count < SYNC_MAX){
        /* aspetta */
        printf("Sono %d!!\n", sync_count);
        rc = pthread_cond_wait(&sync_cond[sync_count-1], &sync_lock);
        if(rc) PrintERROR_andExit(rc, "pthread_cond_wait failed");
        printf("Riveglio %d!!\n", next+1);
        rc = pthread_cond_signal(&sync_cond[next]);
        if(rc) PrintERROR_andExit(rc, "pthread_cond_signal failed");
    
     } else {
        printf("Sono 5 e risveglio 1!!\n");
        rc = pthread_cond_signal(&sync_cond[SYNC_MAX-sync_count]); /* cioè 0 */
        if(rc) PrintERROR_andExit(rc, "pthread_cond_signal failed");        }
    /* sblocca il mutex */ 
	rc = pthread_mutex_unlock (&sync_lock);  /* senza unlock ne termina solo 1 */ 
	if(rc) PrintERROR_andExit(rc,"pthread_mutex_unlock failed"); /* no EINTR */
	return; 
} 

void *Thread (void *arg) {  
	SyncPoint(); 
    pthread_exit(NULL); 
} 

int main () { 
	pthread_t th[SYNC_MAX]; 
	int rc; 
    intptr_t i;
	void *ptr; 

	for(i=0;i<SYNC_MAX;i++) {
		rc = pthread_create(&(th[i]), NULL, Thread, NULL); 
		if (rc) PrintERROR_andExit(rc,"pthread_create failed"); /* no EINTR */
	}
	for(i=0;i<SYNC_MAX;i++) {
		rc = pthread_join(th[i], &ptr ); 
		if (rc) PrintERROR_andExit(rc,"pthread_join failed"); /* no EINTR */
	}
    rc = pthread_mutex_destroy(&sync_lock); 
	if( rc ) PrintERROR_andExit(rc,"pthread_mutex_destroy failed"); /*no EINTR*/
	for(i=0;i<SYNC_MAX;i++){
        rc = pthread_cond_destroy(&sync_cond[i]); 
	    if( rc ) PrintERROR_andExit(rc,"pthread_cond_destroy failed"); /*no EINTR*/
    }
    pthread_exit (NULL); 
} 
  
  
  

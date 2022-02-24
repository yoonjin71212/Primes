#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
#include <math.h>
#include <stdbool.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>
#include <semaphore.h>
clock_t start_time , end_time;
int length;
short thread_Num ;
typedef struct {
	ll start;
	ll end;
	int num;
	list * lst;
} range_t;
sem_t sema;
int fl;
void * t_Prime (void *arg) { 
	range_t * rarg = (range_t *) arg;
	ll start = rarg->start;
	ll end = rarg->end;
	int num = rarg -> num;
	list * lst = rarg->lst;
	ll key ;
	printf ( "starting thread %d\n" ,num );
	register ll i;
	for ( i = start ;size(lst) < end; i+=2 ) {
		bool prflag=true;
		ll endpoint = (ll)sqrt(i)+1;
		for ( key = 3; key < endpoint ; key +=2 ) {
			if (i % key == 0) {
				prflag = false;
				break;
			} 
		}
		sem_wait(&sema);
		if (prflag == true && find (lst , i ) == lst -> rear) {
			push ( lst,i);
			if ( size(lst) == end ) {
				sem_post(&sema);
				break;
			}
		}
		sem_post(&sema);
	}

	return NULL;

}
typedef void * func_prime_t;


int main () {

	sem_init(&sema , 0 , 1);
	list * lst = malloc ( sizeof( list ) ) ;
	init_list (lst);
	push (lst,2);
	ll n;
	printf ( "Threads : " ); 
	scanf("%hd" , &thread_Num );
	printf ( "How much do you want? 5 - ??? " );
	scanf ("%d" , &length );
	if ( length == 1 ) {
		end_time=clock();
		double time_sec = (end_time - start_time) / CLOCKS_PER_SEC;
		printf ( "%lf sec \n" , time_sec);
		printf ("biggest: %lld , %lldth\n" , lst -> rear -> prev -> key , size(lst) );
		exit (0);
	}

	func_prime_t thread_Prime [thread_Num];
	pthread_t pthlist [thread_Num];
	range_t range[thread_Num];
	for ( n = 0 ; n < thread_Num ; n ++ ) {
		thread_Prime[n] = t_Prime;
	}	
	for ( n = 0 ;n<thread_Num; n++ ) {
		if ( n > thread_Num-1 ) {
			n %= thread_Num;
			if ( size(lst) > length ) {
				break;
			}
		}
		range[n].lst = lst;


			range[n].end=length/thread_Num*(n+1);
			if ( n == (thread_Num-1) ){
				range[n].end = length;
			}
			if ( n == 0 ){ 
				range[n].start=3;
			} else {
				range[n].start = lst->rear->prev->key+2;
			}
			if(range[n].start % 2 == 0 ) {
				range[n].start ++;
			}
			range[n].num=n;
			if ( n == 0 ) {
				start_time=clock();
			}
			pthread_create ( (pthlist + (n) ), NULL , thread_Prime[n] , (void *)&range[n] ) ;
	}
	for ( n = 0 ; n < thread_Num ; n++ ) {
			pthread_join( pthlist[n], NULL ) ;
	}

	end_time=clock();
	double time_sec = (end_time - start_time) / CLOCKS_PER_SEC;
	printf ( "%lf sec \n" , time_sec);
	printf ("biggest: %lld , %lldth\n" , lst -> rear -> prev -> key , size(lst) );
	exit (0);


     	    

}

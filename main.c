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
#define EXIT 0
struct timespec start_time , end_time;
short thread_Num ;
typedef struct {
	int start;
	int end;
	int num;
	list * lst;
} range_t;
sem_t sema;
int fl;
void * t_Prime (void *arg) { 
	sem_wait(&sema);
	range_t range_struct = *(range_t *)arg;
	list * thrlist = (list *)range_struct.lst;
	int num = (int)range_struct.num;
	bool prflag;
	int start = (int)range_struct.start;
	int end = (int)range_struct.end;
	register int i=3 ;
	if ( (num == 0 ) | ( size ( thrlist )  <= 1 ) ) {

		register int j;
		for ( i = start ; i < end ; i += 2 ) {
			prflag=true;
			j = 3;
			while ( true ) {
				if ( j >= i ) {
					break;
				} 
				if ( (i % j == 0) ) {
					prflag = false;
					break;
				} 
				j+=2;
					
			}

			if ( (prflag  == true) && (i != 0)) {
				push ( thrlist, i );

			}

		}

	} else {
		node *nd = thrlist -> front -> next;
		int key = thrlist->front->next->key;
		bool prflag;
		while ( key == 0 ) {
			nd = nd -> next;
			key = nd -> key;
		}

		for ( i =start ;i < end ; i+=2 ) {
			prflag=true;
			for ( ; ( key < i ) && ( nd !=thrlist->rear ) ;nd=nd->next ) {
			while ( key == 0 ) {
				nd = nd -> next;
				key = nd -> key;
			}
				if ( i % key == 0 && ( i != key ) ) {
					prflag = false;
					break;
				} 
			}

			while (true) {
				if ( key >= i ) {
					break;
				}
				if ( i % key == 0 ) {
					prflag=false;
					break;
				} 
				key +=2;
			}
			if ( (prflag == true) && (i != 0) ) {
				push ( thrlist,i);
			}
		}
	}
	num ++;

	sem_post(&sema);
	return NULL;

}
typedef void * func_prime_t;


int main () {

	sem_init(&sema , 0 , 1);
	list * lst = malloc ( sizeof( list ) ) ;
	init_list (lst);
	push (lst,2);
	int n,m;
	printf ( "Threads : " ); 
	scanf("%hd" , &thread_Num );
	int length;
	printf ( "How much do you want? 5 - ??? " );
	scanf ("%d" , &length );
	if ( length < 1000 ) {
		bool prflag;
		register int i , j;
		for ( i = 3 ; i < length; i += 2 ) {
			prflag=true;
			j = 3;
			while ( true ) {
				if ( j >= i ) {
					break;
				} 
				if ( (i % j == 0) ) {
					prflag = false;
					break;
				} 
				j+=2;
					
			}

			if ( (prflag  == true) && (i != 0)) {
				push ( lst, i );

			}
		}
		clock_gettime (CLOCK_MONOTONIC , &end_time ); 
		double time_taken = (end_time.tv_sec - start_time.tv_sec) * 1e9 + (end_time.tv_nsec - start_time.tv_nsec) ;
		time_taken *= 1e-9;
		printf ( "%lf s" , time_taken);
		printf ("biggest: %d , %dth\n" , lst -> rear -> prev -> key , size(lst) );
		exit (0);

	}

	func_prime_t thread_Prime [thread_Num];
	pthread_t pthlist [thread_Num];
	range_t range[thread_Num];
	for ( n = 0 ; n < thread_Num ; n ++ ) {
		thread_Prime[n] = t_Prime;
	}	
	clock_gettime( CLOCK_MONOTONIC , &start_time);
	for ( n = 0 , m = 3 ;; n++ , m +=2) {
		if ( n > thread_Num-1 ) {
			static int nn;
			for ( nn = 0 ; nn < thread_Num ; nn ++) {
				pthread_join( pthlist[nn], NULL ) ;
			} 

			n %= thread_Num;
			if ( size(lst) > length ) {
				break;
			}
		}
		range[n].lst = lst;
		auto int mul = m - 2 ;
		if ( mul < 0 ) {
			mul = 0;
		}


		if ( (1000 <= length) && (length < 10000) ) {
			range[n].start=mul*100+3;
			range[n].end=m*100+3;
			range[n].num=n;
		}
		if ( length >= 10000 ) {
			range[n].start=mul*1000+3;
			range[n].end=m*1000+3;
			range[n].num=n;
		}
		pthread_create ( (pthlist + (n) ), NULL , thread_Prime[n] , (void *)&range[n] ) ;

	}
	clock_gettime (CLOCK_MONOTONIC , &end_time ); 
	double time_taken = (end_time.tv_sec - start_time.tv_sec) * 1e9 + (end_time.tv_nsec - start_time.tv_nsec) ;
	time_taken *= 1e-9;
	printf ( "%lf s\n" , time_taken);
	printf ("biggest: %d , %dth\n" , lst -> rear -> prev -> key , size(lst) );
	exit (0);


     	    

}


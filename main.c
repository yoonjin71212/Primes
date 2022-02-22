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
short thread_Num ;
typedef struct {
	ll start;
	ll end;
	ll length;
	ll num ;
	list * lst;
} range_t;
sem_t sema;
ll fl;
void * t_Prime (void *arg) { 
	range_t range_struct = *(range_t *)arg;
	list * lst = (list *)range_struct.lst;
	ll start = (ll)range_struct.start;
	ll end = (ll)range_struct.end;
	ll length = (ll)range_struct.length;
	ll num = (ll)range_struct.num;
	register ll i=3 ;
	node * nd = find ( lst , 3 ) ;
	ll key = nd -> key;
	bool prflag;
	if ( num != 0 && size (lst ) > 2 ) {
		sem_wait(&sema);
	}

	prflag=true;
	for ( i =start ;i < end ; i+=2 ) {
		for ( ; ( key < i ) && ( nd !=lst->rear ) ;nd=nd->next ) {
			while ( key == 0 ) {
				nd = nd -> next;
				key = nd -> key;
			}
			if ( i % key == 0 && ( i != key ) ) {
				prflag = false;
				break;
			} 
		}

		if ( !prflag ) {
			continue;
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
			push ( lst,i);
			if ( size (lst )== length ) {
				return NULL;
			}
		}
	}

	sem_post(&sema);
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
	ll length;
	printf ( "How much do you want? 5 - ??? " );
	scanf ("%lld" , &length );
	if ( length < 4000000 ) {
		bool prflag;
		register ll i , j;
		for ( i = 3 ;; i += 2 ) {
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
				if ( size (lst)==length) {
					break;
				}


			}
		}
		end_time=clock();
		double time_sec = (end_time - start_time) / CLOCKS_PER_SEC;
		printf ( "%lf sec \n" , time_sec);
		printf ("biggest: %lld , %lldth\n" , lst -> rear -> prev -> key , size(lst) );
		exit (0);

	}

	func_prime_t thread_Prime [thread_Num];
	pthread_t pthlist [thread_Num];
	range_t range;
	for ( n = 0 ; n < thread_Num ; n ++ ) {
		thread_Prime[n] = t_Prime;
	}	
	range.end = 0;
	start_time=clock();
	for ( n = 0 ;n < 24; n++ ) {
		if ( n > thread_Num-1 ) {
			static ll nn;
			for ( nn = 0 ; nn < thread_Num ; nn ++) {
				pthread_join( pthlist[nn], NULL ) ;
			} 

			n %= thread_Num;
		}
		range.lst = lst;
		range.num = n;
		range.length=length;
		if ( n != 0 ) {
			range.start=range.end;
		} else {
			range.start=5;
		}	
		range.end+=1000000;
		pthread_create ( (pthlist + (n) ), NULL , thread_Prime[n] , (void *)&range ) ;
		pthread_join ( pthlist[n],NULL);
		show ( lst );
		if ( size ( lst ) == length ){
			break;
		}

	}

	end_time=clock();
	sort_func(lst);
	double time_sec = (end_time - start_time) / CLOCKS_PER_SEC;
	printf ( "%lf sec \n" , time_sec);
	printf ("biggest: %lld , %lldth\n" , lst -> rear -> prev -> key , size(lst) );
	exit (0);


     	    

}


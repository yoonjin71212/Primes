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
clock_t start_time , end_time;
short thread_Num ;
typedef struct {
	ll start;
	ll end;
	ll length;
	list * lst;
} range_t;
ll fl;
void * t_Prime (void *arg) { 
	range_t range_struct = *(range_t *)arg;
	list * lst = (list *)range_struct.lst;
	ll start = (ll)range_struct.start;
	ll end = (ll)range_struct.end;
	ll length = (ll)range_struct.length;
	register ll i=3 ;
	node * nd = find ( lst , 3 ) ;
	ll key = nd -> key;
	bool prflag;

	prflag=true;
	for ( i =start ;; i+=2 ) {
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
			if ( size (lst) == end ) {
				return NULL;
			}
		}
	}

	return NULL;

}
typedef void * func_prime_t;


int main () {

	list * lst = malloc ( sizeof( list ) ) ;
	init_list (lst);
	push (lst,2);
	ll n;
	printf ( "Threads : " ); 
	scanf("%hd" , &thread_Num );
	ll length;
	printf ( "How much do you want? 5 - ??? " );
	scanf ("%lld" , &length );
	bool prflag;
	register ll i , j;
	for ( i = 3 ;i<length; i += 2 ) {
		prflag=true;
		j = 3;
		while ( true ) {
			if ( j >= sqrt(i)+1 ) {
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
		if ( size (lst)==999) {
			break;
		}
	}

	if ( length < 1000 ) {
 
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
	range.end = 1000;
	start_time=clock();
	for ( n = 0 ;; n++ ) {
		range.lst = lst;
		range.length=length;
		range.start= lst -> rear -> prev->key;
		range.end+=100;
		pthread_create ( (pthlist + (n%thread_Num) ), NULL , thread_Prime[n%thread_Num] , (void *)&range ) ;
		pthread_join ( pthlist[n%thread_Num],NULL);
		printf ( "%lld is end of list\n" , lst -> rear -> prev->key );
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


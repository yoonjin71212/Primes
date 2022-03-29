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
struct timespec start_time , end_time;
ll length;
short thread_Num ;
typedef struct {
	int num;
	list * lst;
} range_t;
pthread_mutex_t mutex;
ll save = 0;
void * t_Prime (void *arg) { 
	range_t* rarg = (range_t *) arg;
	int num = rarg -> num + 1;
	list * lst = rarg->lst;
	ll key ;
	printf ( "starting thread %d\n" ,num );
	ll i;
	for (i=3;size(lst) <= length;i+=2) {
		bool prflag=true;
		ll end_Num= (ll)ceil(sqrt(i));
		node * nd = lst -> front -> next;
		key = 3;
		while (key <= end_Num) {
			if ((i % key == 0) && (i != key) ) {
				prflag = false;
				break;
			}
			if ( nd -> key != 0 ) 
				key = key > nd -> key?key:nd->key;
			else 
				key += 2;
			if ( nd == lst -> rear ) {
				break;
			}
			if ( lst -> rear -> prev -> key > i ) {
				i = lst -> rear -> prev -> key;
				end_Num=(ll)ceil(sqrt(i));
			} 
			nd = nd -> next;
		}
		if ( prflag == false ) {
			continue;
		}
		pthread_mutex_lock(&mutex);
		if (prflag == true ) {
			if ( index_node( lst , length )-> key < i ) {
	                         if ( size ( lst ) == length ) {

					  pthread_mutex_unlock(&mutex);
			                  break;
			         }
				push ( lst,i);
				printf ("pushing %lld\n" , i ) ;
			}
			if ( size ( lst ) == length ) {
				pthread_mutex_unlock(&mutex);
				break;
			}
		}
		pthread_mutex_unlock(&mutex);
	}
	return NULL;

}
typedef void * func_prime_t;


int main () {

	pthread_mutex_init(&mutex , NULL);
	list lst; 
	init_list (&lst);
	push (&lst,2);
	ll n;
	printf ( "Threads : " ); 
	scanf("%hd" , &thread_Num );
	printf ( "How much do you want? 5 - ??? " );

	scanf ("%lld" , &length );
	if ( length == 1 ) {
		printf ("biggest: %lld , %lldth\n" , lst.rear -> prev -> key , size(&lst) );
		exit (0);
	} else if ( length < thread_Num ) {
		save = length;
		length *= thread_Num;
	}

	func_prime_t thread_Prime [thread_Num];
	pthread_t pthlist [thread_Num];
	range_t range[thread_Num];
	for ( n = 0 ; n < thread_Num ; n ++ ) {
		thread_Prime[n] = t_Prime;
	}	
	clock_gettime(CLOCK_REALTIME,&start_time);
	for ( n = 0 ;n<thread_Num; n++ ) {
		range[n].lst = &lst;
		range[n].num=n;
		pthread_create ( (pthlist + (n) ), NULL , thread_Prime[n] , (void *)&range[n] ) ;
	}
	for ( n = 0 ; n <thread_Num;n++ ) {
		pthread_join ( pthlist[n],NULL);
	}
	clock_gettime(CLOCK_REALTIME,&end_time);
	double time_sec = ((end_time.tv_sec-start_time.tv_sec)*10000000000.0F - (end_time.tv_nsec - start_time.tv_nsec)) / 10000000000.0F;
	if ( save != 0 ) {
		printf ("%lld , %lldth\n" , index_node( &lst , save-1)->key , save );
		printf ( "%lf sec \n" , time_sec);
	} else {
		printf ("biggest: %lld , %lldth\n" , lst.rear -> prev -> key , size(&lst) );
		printf ( "%lf sec \n" , time_sec);
	}
	exit (0);


    	    

}

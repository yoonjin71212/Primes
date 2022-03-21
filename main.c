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
				push ( lst,i);
				printf ("pushing %lld\n" , i ) ;
			}
			if ( thread_Num != num) {
				if ( size (lst ) >= length/thread_Num*num ) {
					break;
				}
			} 
			if ( size ( lst ) == length ) {
				break;
			}
		}
		pthread_mutex_unlock(&mutex);
	}
	pthread_mutex_unlock(&mutex);
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
	start_time = clock();
	if ( length == 1 ) {
		end_time=clock();
		double time_sec = (end_time - start_time) / CLOCKS_PER_SEC;
		printf ( "%lf sec \n" , time_sec);
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
	for ( n = 0 ;n<thread_Num; n++ ) {
		range[n].lst = &lst;
		range[n].num=n;
		if ( n == 0 )
			start_time=clock();
		pthread_create ( (pthlist + (n) ), NULL , thread_Prime[n] , (void *)&range[n] ) ;
	}
	for ( n = 0 ; n <thread_Num;n++ ) {
		pthread_join ( pthlist[n],NULL);
	}
	end_time=clock();
	double time_sec = (end_time - start_time) / CLOCKS_PER_SEC;
	if ( save != 0 ) {
		printf ("%lld , %lldth\n" , index_node( &lst , save-1)->key , save );
	} else {
		printf ("biggest: %lld , %lldth\n" , lst.rear -> prev -> key , size(&lst) );
		printf ( "%lf sec \n" , time_sec);
	}
	exit (0);


    	    

}

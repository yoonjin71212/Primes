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
	list * lst;
} range_t;
ll save = 0;
void t_Prime (void *arg) { 
	range_t* rarg = (range_t *) arg;
	list * lst = rarg->lst;
	ll key ;
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
		if (prflag == true ) {
			push ( lst,i);
			printf ("pushing %lld\n" , i ) ;
			if ( size ( lst ) == length ) {
				break;
			}
		}
	}

}
int main () {

	list lst; 
	init_list (&lst);
	push (&lst,2);
	printf ( "How much do you want? : " );
	scanf ("%lld" , &length );
	range_t range;
	range.lst = &lst;
	clock_gettime(CLOCK_MONOTONIC,&start_time);
	t_Prime((void *)&range);
	clock_gettime(CLOCK_MONOTONIC,&end_time);
	double time_sec = ((end_time.tv_sec-start_time.tv_sec)*1000000000.0F - (end_time.tv_nsec - start_time.tv_nsec)) / 1000000000.0F;
	if ( save != 0 ) {
		printf ("%lld , %lldth\n" , index_node( &lst , save-1)->key , save );
		printf ( "%lf sec \n" , time_sec);
	} else {
		printf ("biggest: %lld , %lldth\n" , lst.rear -> prev -> key , size(&lst) );
		printf ( "%lf sec \n" , time_sec);
	}
	return 0;


    	    

}

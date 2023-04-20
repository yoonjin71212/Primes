#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>
time_t start_time , end_time;
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
//			printf ("pushing %lld\n" , i ) ;
			if ( size ( lst ) == length ) {
				break;
			}
		}
	}

}
int main (int argc, char **argv) {

  if(argc<2) {
      return 1;
  }
	list lst; 
	init_list (&lst);
	push (&lst,2);
  length=(ll)strtoll(argv[1],NULL,10);
	range_t range;
	range.lst = &lst;
	time(&start_time);
	t_Prime((void *)&range);
	time(&end_time);
	double time_sec = difftime(end_time , start_time);
	if ( save != 0 ) {
		printf ("%lld , %lldth\n" , index_node( &lst , save-1)->key , save );
		printf ( "%ld sec \n" , (long)time_sec);
	} else {
		printf ("biggest: %lld , %lldth\n" , lst.rear -> prev -> key , size(&lst) );
		printf ( "%ld sec \n" , (long)time_sec);
	}
	return 0;


    	    

}

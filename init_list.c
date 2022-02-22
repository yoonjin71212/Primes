#include <stdlib.h>
#include "list.h"
#include <stdbool.h>
void init_list ( list * lst ) { // init list
    lst -> front = ( node * ) malloc ( sizeof ( node ) ) ;
    lst -> rear = ( node * ) malloc( sizeof ( node ) );
    lst -> front -> next = lst -> rear ;
    lst -> rear -> prev = lst -> front ;
    lst -> front -> prev = lst -> front -> prev;
    lst -> rear -> next = lst ->rear ;
    lst -> size = 0 ;
	lst -> is_sorted = true;
}

void reset_list ( list * lst ) { // init list
    lst -> front -> next = lst -> rear ;
    lst -> front -> prev = lst -> front -> prev;
    lst -> rear -> next = lst ->rear ;
    lst -> rear -> prev = lst -> front ;
    lst -> size = 0 ;
	lst -> is_sorted = true;
}

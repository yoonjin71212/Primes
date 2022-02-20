#include <stdlib.h>
#include "list.h"
// function that empties list
void empty_list ( list * lst ) {
    node * element = lst -> front -> next ; // list is first value, that is next of the front node
    while ( element != lst -> rear ) { // while list is not rear node
        free ( element ) ; // free the list
        element = element -> next ; // go to the next node
    }
	lst -> front -> next = lst -> rear ;
	lst -> rear -> prev = lst -> front ;
    lst -> size = 0 ;
}
void free_list ( list * lst ) { // freeing the list
    empty_list ( lst ) ; // first, clear the list
    free ( lst -> front ) ; // free the list -> front
    free ( lst -> rear ) ; // free the list -> rear
}

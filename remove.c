#include <stdio.h>
#include <stdlib.h>
#include "list.h"
/* function that removes the item */
ll remove_item ( list * lst , node * element )
{	
	ll val;
	if ( element == NULL ) {
		val = -1 ;
    } else if ( lst -> size == 0 ) {
        val = -1;
    } else {
		node * x = element -> next;
		node *y = element -> prev ;
        x -> prev = y;
		y -> next = x; 
		val = element -> key ;
        free ( element ) ;
        lst -> size -- ;
    }
	return val ;
}
ll pop_item ( list * lst ) {
	ll i = remove_item ( lst , lst -> rear -> prev ) ;
	return i;
}

#include <stdio.h> 
#include "list.h"
#include <stdbool.h>

// return size of list
int size ( list * lst ) {
	return lst -> size ;
}

// check if list is empty
bool empty ( list * lst ) {
    if ( lst -> size == 0 ) {
        return true ;
	}

    else {
        return false ;
	}
}

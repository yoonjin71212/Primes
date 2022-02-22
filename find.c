#include "list.h"
#include <stdio.h>
#include <stdlib.h>
// find node
node * find ( list * lst, ll key ) {
	node * err;
	if ( ( err = ( node * ) malloc ( sizeof ( node ) ) ) == NULL ) {
		printf("Can't return ERROR NODE") ;
		exit ( 1 );
	} // if memory is too small , exit
	err -> key = -1;
	node * p = lst -> front -> next ;
	while ( p -> key != key ) {
		p = p -> next ;
	}
	if ( p == lst -> rear ) {
		return err ;
	}
	return p;
}
node * index_node ( list * lst , ll i ) {
	node * n = lst -> front -> next ;
	register ll k ;
	for ( k = 0 ; k < i ; k ++ ) {
		if ( n == lst -> rear -> prev ) {
			return n;
		}
	}
	return n;
}

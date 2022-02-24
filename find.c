#include "list.h"
#include <stdio.h>
#include <stdlib.h>
// find node
node * find ( list * lst, ll key ) {
	node * p = lst -> front -> next ;
	while ( p -> key != key ) {
		if ( p == lst -> rear ) {
			return p;
		}
		p = p -> next ;
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

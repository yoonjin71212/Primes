#include "list.h"
#include <stdio.h>
#include <stdlib.h>
// find node
node * find ( list * lst, ll key ) {
	node * p;
	p = lst -> front -> next ;
	while ( p -> key != key ) {
		if ( p == lst -> rear ) {
			break;
		}
		p = p -> next ;
	}
	return p;
}
node * index_node ( list * lst , ll i ) {
	node * n;
	ll k ;
	if ( i > lst -> size / 2) {
		n = lst -> rear -> prev;
		for ( k = 0 ; k < lst -> size - i + 1 ; k ++ ) {
			if ( n == lst -> front ) {
				return lst -> rear;
			}
			n = n -> prev;
		}
	} else {
		n = lst -> front -> next ;
		for ( k = 0 ; k < i ; k ++ ) {
			if ( n == lst -> rear ) {
				break;
			}
		}
		n = n -> next;
	}
	return n;
}

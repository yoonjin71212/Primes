#include "list.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
void sortthree ( list * lst ) {
	node * mid = index_node ( lst , ( int ) ( ( float ) ( lst -> size / 2 ) + 0.5 ) ) ;
	node * front = lst -> front -> next ;
	node * rear = lst -> rear -> prev ;
	if (front -> key > mid -> key ) {
		swap ( &front -> key , &mid -> key );
	}
	if ( front -> key > rear -> key ) {
		swap ( &front -> key , &rear -> key );
	} 
	if ( mid -> key > rear -> key ) {
		swap ( &mid -> key , & rear -> key );
	}
}
void sort_func ( list * lst ) {
	
	if ( lst -> size < 2 ) {
		return;
	}
	int sz = lst -> size ;
	list llst, rlst ;
	init_list ( &llst );
	init_list ( &rlst );
	sortthree( lst );
	node * piv = index_node ( lst , ( int )(rand()%lst->size) ) /*lst -> front -> next*/ , * track = lst -> front -> next ;
	if ( lst -> is_sorted ) {
		return;
	}
	int key = piv -> key;
	for ( ; track != lst -> rear ; track = track -> next ) {
		if ( piv  == track ) {
			track = track -> next ;
			continue;
		}
		if ( track -> key < piv -> key ) {
			push ( &llst , track -> key ) ;
		} else {
			push ( &rlst , track -> key );
		} 
	}
	empty_list ( lst );
	if ( llst.size > 1 ) {
		sort_func ( &llst ) ;
	}
	if ( rlst.size > 1 ) {
		sort_func ( &rlst ) ;
	}
	if ( llst.size > 0 ) { 
/*		track = llst.front -> next ;
		for ( ; track != llst . rear ; track = track -> next ) {
			push ( lst , track -> key );
		} */  
		node * f = llst.front -> next ;
		node * r = llst.rear -> prev ;
		node * left = lst -> front ;
		left -> next = f ;
		f -> prev = left ;
		lst -> rear -> prev = r;
		r -> next = lst -> rear ;
		reset_list ( &llst );
		free_list ( &llst );
	}
	push( lst , key );
	if ( rlst.size > 0 ) { /*
		track = rlst.front -> next ;
		for ( ; track != rlst . rear ; track = track -> next ) {
			push ( lst , track -> key );
		} */ 
		node * f = rlst.front -> next;
		node * r = rlst.rear -> prev;
		node * right = lst -> rear -> prev;
		right -> next = f;
		f -> prev = right;
		r -> next = lst -> rear;
		lst -> rear -> prev = r;
		reset_list ( &rlst );
		free_list ( &rlst );
	}
	lst -> size = sz ;
	lst -> is_sorted = 1;
}
void bubble_sort ( list * lst ) {
	int i ;
	node * n;
	for ( i = 0 ; i < lst -> size ; i ++ ) {
		for ( n = lst -> front -> next ; n -> next != lst -> rear ; n = n -> next ) {
			if ( n -> key > n -> next -> key ) {
				swap ( &n -> key , &n -> next -> key );
			}
		}
	}
} /*
vo sort_func ( list * lst ) {
	if ( ( lst -> size == 0 ) | ( lst -> size == 1 ) ) {
		return ;
	}
	list lst1, lst0;
	init_list ( &lst0 );
	init_list ( &lst1 );
	int size0 = ( int ) ( lst -> size / 2 + 0.5 ) ;
	int size1 = lst -> size - size0;
	node * end0 = lst -> front -> next ;
	node * end1 = lst -> rear -> prev;
	node * n0 = index_node ( lst , size0 ) ;
	node * n1 = split ( n0 ) ;
	lst0 = split_to_list ( n0 , end0 , size0 , true );
	lst0.size = size0;
	lst1 = split_to_list ( n1 , end1 , size1 , false );
	lst1.size = size1;
	merge ( n0 , n1 ) ;
	sort_func ( &lst0 ) ;
	sort_func ( &lst1 );
	lst = complete ( end0 , end1 );
}

list split_to_list ( node * end , node * split , int size_n ,  bool is_front ) {
	static list nlst ;
	init_list ( &nlst );
	if ( is_front ) {
		nlst.size = size_n;
		nlst.rear -> prev = split;
		split -> next = nlst.rear;
		nlst.front -> next = end;
		end -> prev = nlst.front;
	} else {
		nlst.size = size_n;
		nlst.rear -> prev = end;
		end -> next = nlst.rear;
		nlst.front -> next = split;
		split -> prev = nlst.front;
	}
	return nlst;
}
list * complete ( node * first , node * end ) {
	static list nlst;
	init_list ( &nlst );
	nlst.front -> next = first;
	first -> prev = nlst.front;
	nlst.rear -> prev = end;
	end -> next = nlst.rear;
	return &nlst;
}
node * split ( node * a ) {
	node * b = a -> next ;
	a -> next = NULL;
	b -> prev = b;
	return b;
}
void merge ( node * a , node * b ) {
	if ( a -> key > b -> key ) {
		b -> next = a;
		a -> prev = b ;
	} else {
		a -> next = b;
		b -> prev = a;
	}
}*/

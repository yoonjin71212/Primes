#include <stdio.h>
#include "list.h"
/*show list*/
void show( list *lst ) {
    node * t;
    for ( t = lst -> front -> next ; t != lst -> rear ; t = t -> next ) {
        printf ( "%lld\n" , t -> key ) ;
    }
}

#include <stdio.h>
#include "list.h"
//show list
void show( list *lst , FILE * fd ) {
    node * t;
    for ( t = lst -> front -> next ; t != lst -> rear ; t = t -> next ) {
        fprintf ( fd, "%d\n" , t -> key ) ;
    }
}

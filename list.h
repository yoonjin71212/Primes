#define NUM 10
#define LIM 10
#include <stdio.h>
typedef struct node{
	int key;
	struct node *prev;
	struct node *next;
} node;

typedef struct list {
	node *front;
	node *rear;
	int size; 
	_Bool is_sorted;
} list;

void init_list ( list * lst );
void reset_list ( list * lst );
void between  ( list * lst , int item , node * r , node * element ) ;
void regen_sorted ( list * lst );
void push ( list * lst , int item ) ;
void push_list ( list * lst , list * lst_target ) ;
int remove_item ( list * lst , node * element ) ;
int pop_item ( list * lst ) ;
int size ( list *lst ) ;
_Bool empty ( list * lst ) ;
void show ( list * lst , FILE *fd ) ;
void free_list ( list * lst ) ;
void empty_list ( list * lst ) ;
node * find ( list * lst , int key ) ;
node * index_node ( list * lst , int i ) ;
/*void merge ( node * a , node * b );
list * complete ( node * first , node * end );
node * split ( node * a ) ;
list split_to_list ( node * end , node * split , int size_n , _Bool is_front ) ;
*/
void sort_func ( list * lst ) ;
void sortthree ( list * lst ) ;
void bubble_sort ( list * lst );
void swap ( int * a, int * b ); 

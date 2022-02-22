#define NUM 10
#define LIM 10
typedef long long ll;
#include <stdio.h>
typedef struct node{
	ll key;
	struct node *prev;
	struct node *next;
} node;

typedef struct list {
	node *front;
	node *rear;
	ll size; 
	_Bool is_sorted;
} list;

void init_list ( list * lst );
void reset_list ( list * lst );
void between  ( list * lst , ll item , node * r , node * element ) ;
void regen_sorted ( list * lst );
void push ( list * lst , ll item ) ;
void push_list ( list * lst , list * lst_target ) ;
ll remove_item ( list * lst , node * element ) ;
ll pop_item ( list * lst ) ;
ll size ( list *lst ) ;
_Bool empty ( list * lst ) ;
void show ( list * lst ) ;
void free_list ( list * lst ) ;
void empty_list ( list * lst ) ;
node * find ( list * lst , ll key ) ;
node * index_node ( list * lst , ll i ) ;
/*void merge ( node * a , node * b );
list * complete ( node * first , node * end );
node * split ( node * a ) ;
list split_to_list ( node * end , node * split , int size_n , _Bool is_front ) ;
*/
void sort_func ( list * lst ) ;
void sortthree ( list * lst ) ;
void bubble_sort ( list * lst );
void swap ( ll * a, ll * b ); 

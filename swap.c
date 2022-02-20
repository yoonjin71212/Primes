#include "list.h"
// XOR swap
void swap ( int * a , int * b ) {
	if ( * a == * b ) {
		return;
	}

	* a = * a ^ * b;
	* b = * a ^ * b;
	* a = * a ^ * b;
}


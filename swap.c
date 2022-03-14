#include "list.h"
void swap ( ll * a , ll * b ) {
	if ( * a == * b ) {
		return;
	}
	int tmp= *a;
	*a = *b;
	*b = tmp;
}


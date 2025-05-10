#include "stack.h"
#include <stdlib.h>


/*
*  Prove that we can push multiple types in the stack (but this is a bad idea)!
*/
void dangerous_push(stack_t *s) {
	//push a "int" into the stack
	stack_push(s, (void*)1337);

	//push a "int *" into the stack
	int *integer = malloc(sizeof(int));
	*integer = 1024;
	stack_push(s, integer);

	//push "float"
	float *f = malloc(sizeof(float));
	*f = 3.14;
	stack_push(s, f);

	//push "char *"
	char *c = malloc(30 * sizeof(char));
	strcat(c, "store this string in stack");
	stack_push(s, c);
}


int main(void) {
	
}

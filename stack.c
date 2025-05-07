#include "stack.h"
#include <stdlib.h>


/*
 *Push a new element in the stack
 */
void stack_push(stack_t *stack, void *obj) {
	if (stack->count == stack->capacity) {
		stack->capacity *= 2;
		void *new_buf = realloc(stack->data, stack->capacity * sizeof(void *));
		if (new_buf == NULL) {
			stack->capacity /= 2;
			return;
		}
		stack->data = new_buf;
	}
	stack->data[stack->count] = obj;
	stack->count++;
	return;
}

/*
*Create a new stack
*/
stack_t *stack_new(size_t capacity) {
	stack_t * stack = (stack_t*)malloc(sizeof(stack_t));
	if (stack == NULL) {
		return NULL;
	}
	stack->count = 0;
	stack->capacity = capacity;
	stack->data = malloc(capacity * sizeof(void*));

	if (stack == NULL) {
		free(stack);
		return NULL;
	}
	return stack;
}

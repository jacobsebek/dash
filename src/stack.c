#include "stack.h"

vector* stack_create(int (*destroy_element)(void*))
{
	return vector_create(destroy_element);
}

int stack_push(stack* stk, void* element)
{
	return vector_append(stk, element);
}

void* stack_pop(stack* stk)
{
	void* e = vector_get(stk, stack->length-1);
	vector_remove(stack, stack->length-1);
	return e;
}

int stack_destroy(stack* stk)
{
	return vector_destroy(stk);
}

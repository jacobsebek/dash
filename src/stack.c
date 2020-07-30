#include "dash/stack.h"
// TODO: this can be optimized by storing only the top and bottom of the stack

ds_stack* stack_create(int (*destroy_element)(void*))
{
	return vector_create(destroy_element);
}

int stack_push(ds_stack* stack, void* element)
{
	return vector_append(stack, element);
}

void* stack_pop(ds_stack* stack)
{
	void* e = vector_get(stack, stack->length-1);
	vector_remove(stack, stack->length-1);
	return e;
}

int stack_destroy(ds_stack* stack)
{
	return vector_destroy(stack);
}

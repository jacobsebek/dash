#include "dash/queue.h"

queue* queue_create(int (*destroy_element)(void*))
{
	return vector_create(destroy_element);
}

int queue_push(queue* que, void* element)
{
	return vector_append(que, element);
}

void* queue_pop(queue* que)
{
	void* e = vector_get(que, 0);
	vector_remove(que, 0);
	return e;
}

int queue_destroy(queue* que)
{
	return vector_destroy(que);
}

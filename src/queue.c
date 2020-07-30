#include "dash/queue.h"

ds_queue* queue_create(int (*destroy_element)(void*))
{
	return vector_create(destroy_element);
}

int queue_push(ds_queue* que, void* element)
{
	return vector_append(que, element);
}

void* queue_pop(ds_queue* que)
{
	void* e = vector_get(que, 0);
	vector_remove(que, 0);
	return e;
}

int queue_destroy(ds_queue* que)
{
	return vector_destroy(que);
}

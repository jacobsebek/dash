#pragma once

#include "dash/dash.h"
#include "dash/vector.h"

typedef vector queue;

queue* queue_create(int (*destroy_element)(void*));
int queue_push(queue* que, void* element);
void* queue_pop(queue* que);
int queue_destroy(queue* que);

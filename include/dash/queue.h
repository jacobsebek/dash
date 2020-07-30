#pragma once

#include "dash/dash.h"
#include "dash/vector.h"

typedef ds_vector ds_queue;

ds_queue* queue_create(int (*destroy_element)(void*));
int queue_push(ds_queue* que, void* element);
void* queue_pop(ds_queue* que);
int queue_destroy(ds_queue* que);

#pragma once

#include "dash/dash.h"
#include "dash/vector.h"

typedef ds_vector ds_stack;

ds_stack* stack_create(int (*destroy_element)(void*));
int stack_push(ds_stack* stack, void* element);
void* stack_pop(ds_stack* stack);
int stack_destroy(ds_stack* stack);

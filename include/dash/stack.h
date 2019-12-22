#pragma once

#include "dash/dash.h"
#include "dash/vector.h"

typedef vector stack;

stack* stack_create(int (*destroy_element)(void*));
int stack_push(stack* stk, void* element);
void* stack_pop(stack* stk);
int stack_destroy(stack* stk);

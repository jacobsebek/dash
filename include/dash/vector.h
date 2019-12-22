#pragma once

#include "dash/dash.h"

typedef struct vector {
	void** first; // The array
	uint length; // Number of elements
	uint size; // Allocated memory in bytes
	const int (*destroy_element)(void*);
} vector;

vector* vector_create(int (*destroy_element)(void*));

int vector_append(vector* vec, void* element);
int vector_push(vector* vec, void* element);
int vector_insert(vector* vec, void* element, uint index);

void* vector_get(vector* vec, uint index);
uint vector_getIndex(vector* vec, void* element);
uint vector_getLength(vector* vec);

int vector_remove(vector* vec, uint index);
int vector_destroy(vector* vec);

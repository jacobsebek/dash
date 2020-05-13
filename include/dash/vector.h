#pragma once

#include "dash/dash.h"

typedef struct vector {
	void** first; // The array
	size_t length; // Number of elements
	size_t size; // Allocated memory in bytes
	const int (*destroy_element)(void*);
} vector;

vector* vector_create(int (*destroy_element)(void*));

int vector_append(vector* vec, void* element);
int vector_push(vector* vec, void* element);
int vector_insert(vector* vec, void* element, size_t index);

void* vector_get(vector* vec, size_t index);
size_t vector_getIndex(vector* vec, void* element);
size_t vector_getLength(vector* vec);

int vector_remove(vector* vec, size_t index);
int vector_destroy(vector* vec);

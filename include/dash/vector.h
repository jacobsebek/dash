#pragma once

#include "dash/dash.h"

typedef struct ds_vector {
	void** first; // The array
	size_t length; // Number of elements
	size_t size; // Allocated memory in bytes
	const int (*destroy_element)(void*);
} ds_vector;

ds_vector* vector_create(int (*destroy_element)(void*));

int vector_append(ds_vector* vec, void* element);
int vector_push(ds_vector* vec, void* element);
int vector_insert(ds_vector* vec, void* element, size_t index);

void* vector_get(ds_vector* vec, size_t index);
size_t vector_index(ds_vector* vec, void* element);
size_t vector_length(ds_vector* vec);

int vector_remove(ds_vector* vec, size_t index);
int vector_destroy(ds_vector* vec);

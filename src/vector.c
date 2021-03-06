#include "dash/vector.h"
#include <stdlib.h>
#include <string.h>

ds_vector* vector_create(int (*destroy_element)(void*))
{
	ds_vector* vec = malloc(sizeof(ds_vector));

	vec -> size = sizeof(void*); // Starting on a size of 1
	vec -> first = malloc(vec->size);
	vec -> length = 0;
	vec -> destroy_element = destroy_element;

	//for (int i = 0; i < vec->size/sizeof(void*); i++) vec->first[i] = NULL;

	return vec;
}

int vector_insert(ds_vector* vec, void* element, size_t index)
{
	if (!vec || !element) return DASH_NULLARG;
	if (index > vec->length) return DASH_MEMFAULT;

	if (vec->length+1 > vec->size/sizeof(void*))
		vec -> first = realloc(vec->first, vec->size*=2);

	if (vec->first == NULL) return DASH_MEMFAULT;

	memmove(vec->first+(index+1), vec->first+(index), (vec->length-index)*sizeof(void*));
	
	vec->length++;

	vec->first[index] = element;

	return DASH_OK;
}

int vector_append(ds_vector* vec, void* element) 
{
	vector_insert(vec, element, vec->length);
}

int vector_push(ds_vector* vec, void* element)
{
	vector_insert(vec, element, 0);
}

void* vector_get(ds_vector* vec, size_t index)
{
	if (vec != NULL && index < vec->length)
		return vec->first[index]; //also &vec->first[index]
	else return NULL;
}

size_t vector_index(ds_vector* vec, void* element)
{
	if (vec == NULL) return vec->length;

	for (size_t i = 0; i < vec->length; i++)
		if (vector_get(vec, i) == element) return i;

	return vec->length;
}

size_t vector_length(ds_vector* vec)
{
	if (vec == NULL) return DASH_NULLARG;
	return vec->length;
}

int vector_remove(ds_vector* vec, size_t index)
{

	if (vec == NULL) return DASH_NULLARG;
	if (index >= vec->length) return DASH_MEMFAULT;

	register int returnval = vec->destroy_element(vector_get(vec, index));
	memmove(vec->first+(index), vec->first+(index+1), (vec->length-index-1)*sizeof(void*));

	vec->length--;

	return returnval;
}

int vector_destroy(ds_vector* vec) 
{
	if (vec == NULL) return DASH_NULLARG;

	for (size_t i = 0; i < vec->length; i++) {
		void* e = vector_get(vec, i);
		if (vec->destroy_element != NULL) vec->destroy_element(e);
	}

	free(vec->first);
	free(vec);

	return DASH_OK;
}

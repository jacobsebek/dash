#include "vector.h"
#include <stdlib.h>
#include <string.h>

vector* vector_create(int (*destroy_element)(void*))
{
	vector* vec = malloc(sizeof(vector));

	vec -> size = sizeof(void*); // Starting on a size of 1
	vec -> first = malloc(vec->size);
	vec -> length = 0;
	vec -> destroy_element = destroy_element;

	//for (int i = 0; i < vec->size/sizeof(void*); i++) vec->first[i] = NULL;

	return vec;
}

int vector_insert(vector* vec, void* element, uint index)
{
	if (!vec || !element) return DASH_NULLARG;
	if (index > vec->length) return DASH_MEMFAULT;

	if (vec->length+1 > vec->size/sizeof(void*))
		vec -> first = realloc(vec->first, vec->size*=2);

	if (vec->first == NULL) return DASH_MEMFAULT;

	memmove(vec->first+(index+1), vec->first+(index), (vec->length-index)*sizeof(void*));
	
	vec->length++;

	//vec->first[index] = element;
	memcpy(vec->first+index, element, sizeof(void*));

	return DASH_OK;
}

int vector_append(vector* vec, void* element) 
{
	vector_insert(vec, element, vec->length);
}

int vector_push(vector* vec, void* element)
{
	vector_insert(vec, element, 0);
}

void* vector_get(vector* vec, uint index)
{
	if (index < vec->length && vec != NULL)
		return vec->first+index; //also &vec->first[index]
	else return NULL;
}

uint vector_getIndex(vector* vec, void* element)
{
	if (vec == NULL) return 0;

	for (uint i = 0; i < vec->length; i++)
		if (vector_get(vec, i) == element) return i;

	return vec->length;
}

uint vector_getLength(vector* vec)
{
	if (vec == NULL) return DASH_NULLARG;
	return vec->length;
}

int vector_remove(vector* vec, uint index)
{

	if (vec == NULL) return DASH_NULLARG;
	if (index >= vec->length) return DASH_MEMFAULT;

	memmove(vec->first+(index), vec->first+(index+1), (vec->length-index-1)*sizeof(void*));

	vec->length--;

	return DASH_OK;
}

int vector_destroy(vector* vec) 
{
	if (vec == NULL) return DASH_NULLARG;

	for (uint i = 0; i < vector_getLength(vec); i++) {
		void* e = vector_get(vec, i);
		if (vec->destroy_element != NULL) (*vec->destroy_element)(e);
	}

	free(vec->first);
	free(vec);

	return DASH_OK;
}

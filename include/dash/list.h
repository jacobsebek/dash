#pragma once

#include "dash/dash.h"

#define list_iter_getnext(iter, type) ((type)list_iter_next(iter))

typedef struct ds_list_node {
	void* data;
    struct ds_list_node *next, *prev;
} ds_list_node;

typedef struct ds_list {
	ds_list_node *head; // head->next is the first element, head->prev is the last one
	const int (*destroy_element)(void*);
}  ds_list;

typedef struct ds_iterator {
	ds_list_node* node;
	ds_list* list;
} ds_iterator;

ds_list* list_create(int (*destroy_element)(void*));

int list_append(ds_list* ls, void* element);
int list_prepend(ds_list* ls, void* element);

ds_iterator list_iter_start(ds_list* ls); // Returns a new iterator
void* list_iter_next(ds_iterator* iter); // Proceeds the iterator to the next element. If the next element is null, returns non-null value
_Bool list_iter_hasnext(ds_iterator* iter);
int list_iter_remove(ds_iterator* iter); // Removes the current iterated node (and the iterator is set to the previous one)

int list_destroy(ds_list* ls);

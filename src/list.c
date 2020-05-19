#include "dash/list.h"

#include <stdlib.h>

ds_list* list_create(int (*destroy_element)(void*)) {
	ds_list* ls = malloc(sizeof(ds_list));	
	ls->destroy_element = destroy_element;
	ls->head = malloc(sizeof(ds_list_node));
	ls->head->next = ls->head;
	ls->head->prev = ls->head;

	return ls;
}

int list_append(ds_list* ls, void* element) {

	if (ls == NULL) return DASH_NULLARG;

	ds_list_node* node = malloc(sizeof(ds_list_node));
	node->data = element;
	node->prev = ls->head->prev; // setting new last's prev to former last
	node->next = ls->head; // last's element is set to head to wrap around and determine end of the list
	
	ls->head->prev->next = node;
	ls->head->prev = node;	

	return DASH_OK;
}

int list_prepend(ds_list* ls, void* element) {

	if (ls == NULL) return DASH_NULLARG;

	ds_list_node* node = malloc(sizeof(ds_list_node));
	node->data = element;
	node->prev = ls->head; // setting new last's prev to former last
	node->next = ls->head->next;
	
	ls->head->next->prev = node;
	ls->head->next = node;	

	return DASH_OK;
}

// Iterators

// Returns a new iterator
ds_iterator list_iter_start(ds_list* ls) { 
	if (ls == NULL) return (ds_iterator){NULL, NULL};

	ds_iterator iter;
	iter.node = ls->head;
	iter.list = ls;

	return iter;
}

// Proceeds the iterator to the next element.
void* list_iter_next(ds_iterator* iter) {

	// return NULL if iterator is NULL, or its node is NULL
	if (iter == NULL || iter->node == NULL) return NULL;

	if (iter->node->next == iter->list->head)
		iter->node = iter->list->head->next; // Allows skipping the head and wrapping right to the first element
	else
		iter->node = iter->node->next; 

	return iter->node->data;
}

_Bool list_iter_hasnext(ds_iterator* iter) {
	return !(iter == NULL || iter->node == NULL || iter->node->next == NULL
			 || iter->node->next == iter->list->head); // break out if the node is pointing back to head
}

// Removes the current iter->ted node (and the iterator is set to the previous one)
int list_iter_remove(ds_iterator* iter) {

	// This has to be guranteed not to delete the list head!!!
	if (iter == NULL || iter->node == NULL || iter->node == iter->list->head) return DASH_NULLARG;

	if (iter->node->prev != NULL)
		iter->node->prev->next = iter->node->next;
	
	if (iter->node->next != NULL) 
		iter->node->next->prev = iter->node->prev;

	int returnval = DASH_OK;
	if (iter->list->destroy_element != NULL)
		returnval = iter->list->destroy_element(iter->node->data);
 
	// This pointer wouldnt be accesible after free
	register ds_list_node* jump = iter->node->prev;
	free(iter->node);

	iter->node = jump;

	return returnval;
}

int list_destroy(ds_list* ls) {

	if (ls == NULL) return DASH_NULLARG; 
	
	for (ds_iterator iter = list_iter_start(ls); list_iter_hasnext(&iter); ) { 
		list_iter_next(&iter);
		list_iter_remove(&iter);		
	}	

	free(ls);

	return DASH_OK;

}

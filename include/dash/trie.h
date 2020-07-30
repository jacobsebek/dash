#pragma once

#include "dash/dash.h"
#include "dash/vector.h"
#include "dash/string.h"
#define TRIE_BRANCHES 100

typedef struct ds_trie {
	void* data;
	struct ds_trie *children[TRIE_BRANCHES];
} ds_trie;

typedef struct ds_trie_dump {
	void* data;
	ds_string name;
} ds_trie_dump;

ds_trie* trie_create();

// When using trie_remove, it is your responsibility to free the data!!
// This is not the case in trie_destroy, where you can specify the freeing function because of convenience
int trie_destroy(ds_trie* trie, void (*destroy_element)(void*));
void* trie_remove(ds_trie* trie, const char* key, const unsigned char (*cencode)(const char));
ds_vector* trie_dump(ds_trie* trie, const char (*cdecode)(const unsigned char));

int trie_add(ds_trie* trie, const char* key, const unsigned char (*cencode)(const char), void* data);
void* trie_find(const ds_trie* trie, const char* key, const unsigned char (*cencode)(const char));

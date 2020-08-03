#include "dash/trie.h"

#include <stdlib.h> // calloc, free

ds_trie* trie_create() {
	return calloc(1, sizeof(ds_trie));
}

int trie_destroy(ds_trie* trie, void (*destroy_element)(void*)) {
	if (trie == NULL) return DASH_NULLARG;

	for (size_t i = 0; i < TRIE_BRANCHES; i++)
		trie_destroy(trie->children[i], destroy_element);

	if (trie->data != NULL && destroy_element != NULL)
		destroy_element(trie->data);

	free(trie);	

	return DASH_OK;
}

int trie_add(ds_trie* trie, const char* key, const unsigned char (*cencode)(const char), void* data) {
	if (trie == NULL || key == NULL) return DASH_NULLARG;
	
	// The node will move down the tree, creating new nodes if needed
	for (const char* c = key; *c != '\0'; c++) {
		char i = (cencode == NULL ? *c : cencode(*c));	

		if (trie->children[i] == NULL)
			trie->children[i] = trie_create();

		trie = trie->children[i];	
	}

	trie->data = data;

	return DASH_OK;

}

static _Bool has_children(ds_trie* trie, _Bool ignore, size_t index_ignore) {

	for (size_t i = 0; i < TRIE_BRANCHES; i++)
		if (!(ignore && i == index_ignore) && trie->children[i] != NULL)
			return 1;

	return 0;
}

void* trie_remove(ds_trie* trie, const char* key, const unsigned char (*cencode)(const char)) {
	if (trie == NULL || key == NULL) return NULL;
	
	// Used to store the position of the last node that cannot be deleted,
	// because it either holds data or has more than 1 child
	ds_trie* last_fork = NULL;
	// The "dead branch" child of the last fork (last_fork[last_fork_child] is the tree to be removed)
	unsigned char last_fork_child = 0;

	for (const char* c = key; *c != '\0'; c++) {
		unsigned char branch = (cencode == NULL ? *c : cencode(*c));	
		if (branch >= TRIE_BRANCHES) return NULL; // Invalid character - out of bounds

		_Bool is_dead = 1;

		if (trie->data != NULL || c-key == 0) is_dead = 0;
		else
			is_dead = !has_children(trie, 1, branch);

		if (!is_dead) {
			last_fork = trie;
			last_fork_child = branch;
		}

		// Branch to the next node
		trie = trie->children[branch];
		if (trie == NULL) return NULL; // Word does not exist
	}

	if (last_fork == NULL) return NULL;

	void* data = trie->data;

	if (!has_children(trie, 0, 0)) {
		trie_destroy(last_fork->children[last_fork_child], NULL);
		last_fork->children[last_fork_child] = NULL;
	} else {
		trie->data = NULL;		
	}

	return data;
	
}

void* trie_find(const ds_trie* trie, const char* key, const unsigned char (*cencode)(const char)) {
	if (trie == NULL || key == NULL) return NULL;

	for (const char* c = key; *c != '\0'; c++) {
		unsigned char i = (cencode == NULL ? *c : cencode(*c));	
		if (i >= TRIE_BRANCHES) return NULL; // Invalid character - out of bounds

		trie = trie->children[i];

		if (trie == NULL) return NULL; // Word does not exist
	}
	
	return trie->data;

}

// -----------dumping
static int dump_destroy(ds_trie_dump* dump) {
	string_destroy(dump->name);
	free(dump);
	return DASH_OK;
}

static void trie_dump_rec(ds_trie* trie, ds_vector* vec, ds_string* currstr, const char (*cdecode)(const unsigned char)) {
	
	if (trie == NULL) return;

	for (size_t i = 0; i < TRIE_BRANCHES; i++) {
		if (trie->children[i] == NULL) continue;
		char branch = (cdecode == NULL ? i : cdecode(i));	

		string_append(currstr, DS_CTOS(branch));
		trie_dump_rec(trie->children[i], vec, currstr, cdecode);
		string_destroy(string_trim(currstr, 0, string_length(*currstr)-1));
	}

	if (trie->data != NULL && vec != NULL) {
		ds_trie_dump* dump = malloc(sizeof(ds_trie_dump));

		dump->data = trie->data;
		dump->name = string_create(*currstr);
		vector_append(vec, dump);
	}

}

ds_vector* trie_dump(ds_trie* trie, const char (*cdecode)(const unsigned char)) {
	ds_vector* vec = vector_create((int (*)(void*))dump_destroy);

	ds_string str = string_create(NULL);

	trie_dump_rec(trie, vec, &str, cdecode);

	string_destroy(str);
	return vec;
}


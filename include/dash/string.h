#pragma once

#include "dash/dash.h"

#define DS_CTOS(c) (char[2]){c, '\0'} 

typedef char* ds_string;

ds_string string_create(ds_string src);
ds_string string_create_c(char c);

int string_destroy(ds_string* str);

int string_insert(ds_string* dst, const ds_string src, const size_t pos);
int string_append(ds_string* dst, const ds_string src);
int ds_string_prepend(ds_string* dst, const ds_string src);

size_t string_find(const ds_string str, const ds_string key, const size_t start, const size_t end);

ds_string string_substring(const ds_string str, const size_t start, const size_t end);
ds_string string_trim(ds_string* str, const size_t start, const size_t end);
ds_string string_cut(ds_string* str, const size_t start, const size_t end);

int string_replace(ds_string* dst, const ds_string src, const size_t start, const size_t end);
int string_replace_all(ds_string* dst, const ds_string key, const ds_string src);

int string_to_lower(ds_string* str);
int string_to_upper(ds_string* str);

int string_copy(ds_string* dst, const ds_string src);
int string_move(ds_string* dst, const ds_string src);
_Bool string_equals(const ds_string str1, const ds_string str2);

int ds_string_print(const ds_string str);
int ds_string_print_dec(const ds_string str);

size_t string_length(const ds_string str);

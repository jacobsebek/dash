#pragma once

#include "dash/dash.h"

#define DS_CTOS(c) (char[2]){c, '\0'} 

typedef char* ds_string;

ds_string string_create_buf(size_t length);
ds_string string_create(const char* src);
ds_string string_create_c(const char c);

int string_destroy(ds_string str);

int string_insert(ds_string* dst, ds_string src, const size_t pos);
int string_append(ds_string* dst, ds_string src);
int string_prepend(ds_string* dst, ds_string src);

size_t string_find(ds_string str, ds_string key, const size_t start, const size_t end);

ds_string string_substring(ds_string str, const size_t start, size_t end);
ds_string string_trim(ds_string* str, const size_t start, size_t end);
ds_string string_cut(ds_string* str, const size_t start, const size_t end);

int string_replace(ds_string* dst, ds_string src, const size_t start, const size_t end);
int string_replace_all(ds_string* dst, ds_string key, ds_string src);

int string_to_lower(ds_string str);
int string_to_upper(ds_string str);

int string_copy(ds_string dst, ds_string src);
int string_change(ds_string* dst, ds_string src);
_Bool string_equals(ds_string str1, ds_string str2);

size_t string_length(ds_string str);

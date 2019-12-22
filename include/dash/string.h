#pragma once

#include "dash/dash.h"

typedef char* string;

string string_create(string src);
string string_create_c(char c);

int string_destroy(string str);

int string_insert(string* dst, string src, uint pos);
int string_append(string* dst, string src);
int string_prepend(string* dst, string src);

uint string_find(string str, string key, uint start, uint end);

string string_substring(string str, uint start, uint end);
int string_trim(string* str, uint start, uint end);
string string_cut(string* str, uint start, uint end);

int string_replace(string* dst, string src, uint start, uint end);
int string_replace_all(string* dst, string key, string src);

int string_to_lower(string* str);
int string_to_upper(string* str);

int string_set(string* dst, string src);
bool string_equals(string str1, string str2);

int string_print(string str);
int string_print_dec(string str);

uint string_length(string str);

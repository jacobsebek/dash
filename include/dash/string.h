#pragma once

#include "dash/dash.h"

#define CTOS(c) (char[2]){c, '\0'} 

typedef char* string_p;

string_p string_create(string_p src);
string_p string_create_c(char c);

int string_destroy(string_p* str);

int string_insert(string_p* dst, const string_p src, const uint pos);
int string_append(string_p* dst, const string_p src);
int string_prepend(string_p* dst, const string_p src);

uint string_find(const string_p str, const string_p key, const uint start, const uint end);

string_p string_substring(string_p* str, const uint start, const uint end);
int string_trim(string_p* str, const uint start, const uint end);
string_p string_cut(string_p* str, const uint start, const uint end);

int string_replace(string_p* dst, const string_p src, const uint start, const uint end);
int string_replace_all(string_p* dst, const string_p key, const string_p src);

int string_to_lower(string_p* str);
int string_to_upper(string_p* str);

int string_copy(string_p* dst, const string_p src);
int string_move(string_p* dst, const string_p src);
bool string_equals(const string_p str1, const string_p str2);

int string_print(const string_p str);
int string_print_dec(const string_p str);

uint string_length(const string_p str);

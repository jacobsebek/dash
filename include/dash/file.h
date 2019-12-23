#pragma once

#include "dash/dash.h"
#include <dash/string.h>

#include <stdio.h>

typedef FILE* file;

file file_open(string_p name);
int file_close(file file);

int file_create(string_p name);
int file_remove(string_p name);
int file_clear(file file);

bool file_eof(file file);

string_p file_get_line(file file);
string_p file_get_string(file file, uint len);
char file_get_char(file file);
int file_rewind(file file);

int file_append(file file, string_p src);

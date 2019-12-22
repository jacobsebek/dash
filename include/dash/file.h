#pragma once

#include "dash/dash.h"
#include <dash/string.h>

#include <stdio.h>

typedef FILE* file;

file file_open(string name);
int file_close(file file);

int file_create(string name);
int file_remove(string name);
int file_clear(file file);

bool file_eof(file file);

string file_get_line(file file);
string file_get_string(file file, uint len);
int file_get_char(file file);
int file_rewind(file file);

int file_append(file file, string src);

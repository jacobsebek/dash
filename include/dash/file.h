#pragma once

#include "dash/dash.h"
#include <dash/string.h>

#include <stdio.h>

typedef FILE* file;

file file_open(ds_string name);
int file_close(file file);

int file_create(ds_string name);
int file_remove(ds_string name);
int file_clear(file file);

bool file_eof(file file);

ds_string file_get_line(file file);
ds_string file_get_string(file file, size_t len);
char file_get_char(file file);
int file_rewind(file file);

int file_append(file file, ds_string src);

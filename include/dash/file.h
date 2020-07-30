#pragma once

#include "dash/dash.h"
#include "dash/string.h"

#include <stdio.h>

typedef FILE ds_file;

ds_file* file_open(ds_string name);
int file_close(ds_file* file);

int file_create(ds_string name);
int file_remove(ds_string name);
int file_clear(ds_file* file);

_Bool file_eof(ds_file* file);

ds_string file_get_line(ds_file* file);
ds_string file_get_string(ds_file* file, size_t len);
char file_get_char(ds_file* file);
int file_rewind(ds_file* file);

int file_append(ds_file* file, ds_string src);

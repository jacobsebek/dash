#include "dash/file.h"
#include <stdio.h>

ds_file* file_open(ds_string name)
{
	if (name == NULL) return NULL;
	return fopen(name, "a+");
}

int file_close(ds_file* file)
{
	if (file == NULL) return DASH_NULLARG;
	return !fclose(file) ? DASH_OK : DASH_MEMFAULT;
}

int file_create(ds_string name)
{
	if (name == NULL) return DASH_NULLARG;
	return !fclose(fopen(name, "w")) ? DASH_OK : DASH_MEMFAULT;
}

int file_remove(ds_string name)
{
	if (name == NULL) return DASH_NULLARG;
	return !remove(name) ? DASH_OK : DASH_MEMFAULT;
}

int file_clear(ds_file* file)
{
	return freopen(NULL, "w", file) == NULL ? DASH_MEMFAULT : DASH_OK;
}

_Bool file_eof(ds_file* file)
{
	if (file == NULL) return DASH_NULLARG;

	return feof(file);
}

ds_string file_get_line(ds_file* file)
{
	if (file == NULL) return NULL;

	ds_string str = string_create(NULL);

	char c;
	while ( (c = fgetc(file)) != '\n' && !feof(file))
		string_append(&str, DS_CTOS(c));

	return str;
}

ds_string file_get_string(ds_file* file, size_t len)
{
	if (file == NULL) return NULL;

	ds_string str = string_create(NULL);

	char c;
	for (size_t i = 0; i < len && (c = fgetc(file)) != EOF; i++)
		string_append(&str, DS_CTOS(c));

	return str;
}

char file_get_char(ds_file* file)
{
	if (file == NULL) return '\0';

	int c = fgetc(file);
	return c != EOF ? (char)c : '\0';
}

int file_rewind(ds_file* file)
{
	if (file == NULL) return DASH_NULLARG;

	return !fseek(file, 0, SEEK_SET) ? DASH_OK : DASH_MEMFAULT;
}

int file_append(ds_file* file, ds_string src)
{
	if (file == NULL || src == NULL) return DASH_NULLARG;

	size_t srclen = string_length(src);
	for (size_t i = 0; i < srclen; i++)
		if (fputc(src[i], file) == EOF) return DASH_MEMFAULT;

	return DASH_OK;
}

#include <stdio.h>

#include "dash/dash.h"
#include "dash/file.h"
#include "dash/string.h"

file file_open(string_p name)
{
	if (name == NULL) return NULL;
	return fopen(name, "a+");
}

int file_close(file file)
{
	if (file == NULL) return DASH_NULLARG;
	return !fclose(file) ? DASH_OK : DASH_MEMFAULT;
}

int file_create(string_p name)
{
	if (name == NULL) return DASH_NULLARG;
	return !fclose(fopen(name, "w")) ? DASH_OK : DASH_MEMFAULT;
}

int file_remove(string_p name)
{
	if (name == NULL) return DASH_NULLARG;
	return !remove(name) ? DASH_OK : DASH_MEMFAULT;
}

int file_clear(file file)
{
	return freopen(NULL, "w", file) == NULL ? DASH_MEMFAULT : DASH_OK;
}

bool file_eof(file file)
{
	if (file == NULL) return DASH_NULLARG;

	return feof(file);
}

string_p file_get_line(file file)
{
	if (file == NULL) return NULL;

	string_p str = string_create(NULL);

	char c;
	while ( (c = fgetc(file)) != '\n' && !feof(file)) {
		char cstr[2] = {c, '\0'};
		string_append(&str, cstr);
	}

	return str;
}

string_p file_get_string(file file, uint len)
{
	if (file == NULL) return NULL;

	string_p str = string_create(NULL);

	int c;
	for (uint i = 0; i < len && (c = fgetc(file)) != EOF; i++) {
		char cstr[2] = {c, '\0'};
		string_append(&str, cstr);
	}

	return str;
}

char file_get_char(file file)
{
	if (file == NULL) return '\0';

	int c = fgetc(file);
	return c ? (char)c : '\0';
}

int file_rewind(file file)
{
	if (file == NULL) return DASH_NULLARG;

	return !fseek(file, 0, SEEK_SET) ? DASH_OK : DASH_MEMFAULT;
}

int file_append(file file, string_p src)
{
	if (file == NULL || src == NULL) return DASH_NULLARG;

	uint srclen = string_length(src);
	for (uint i = 0; i < srclen; i++)
		if (fputc(src[i], file) == EOF) return DASH_MEMFAULT;

	return DASH_OK;
}

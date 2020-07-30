#include "dash/string.h"
#include <string.h>
#include <stdlib.h>

ds_string string_create_buf(const size_t length) {
	return calloc(length+1, sizeof(char));
}

ds_string string_create(const char* src)
{
	if (src == NULL) src = "";

	ds_string str = string_create_buf(strlen(src));
	strcpy(str, src);
	return str;
}

ds_string string_create_c(const char c)
{
	char str[2] = {c, '\0'};
	return string_create(str);
}

int string_destroy(ds_string str)
{
	if (str == NULL) return DASH_NULLARG;
	free(str);
	return DASH_OK;
}

int string_insert(ds_string* dst, ds_string src, const size_t pos)
{
	if (dst == NULL || *dst == NULL || src == NULL) return DASH_NULLARG;

	size_t dstlen = strlen(*dst), 
		   srclen = strlen(src);

	if (pos > dstlen) return DASH_MEMFAULT;

	*dst = realloc(*dst, (dstlen+srclen+1)*sizeof(char));

	memmove(*dst+pos+srclen, *dst+pos, sizeof(char)*(dstlen-pos)); 
	memcpy(*dst+pos, src, sizeof(char)*srclen);
	(*dst)[dstlen+srclen] = '\0';

	return DASH_OK;
}

int string_append(ds_string* dst, ds_string src) // [ABC0] + [1230] = [ABC0---], [ABC1230]
{
	if (dst == NULL) return DASH_NULLARG;

	size_t pos;
	if (*dst != NULL) pos = strlen(*dst);

	return string_insert(dst, src, pos);
}

int string_prepend(ds_string* dst, ds_string src)
{
	return string_insert(dst, src, 0);
}

size_t string_find(ds_string str, ds_string key, const size_t start, const size_t end)
{
	if (str == NULL || key == NULL || 
		end < start || end > strlen(str)) return end;

	size_t keylength = strlen(key);

	size_t matches = 0;
	for (size_t i = start; i < end; i++)
		if (str[i] == key[matches]) {
			if (++matches == keylength) return i-keylength+1;
		} else matches = 0;

	return end;
}

ds_string string_substring(ds_string str, const size_t start, const size_t end)
{
	if (str == NULL || end < start || end > strlen(str)) return NULL;

	ds_string new = string_create_buf(end-start);
	memcpy(new, str+start, sizeof(char)*(end-start));
	new[end-start] = '\0';

	return new;
}

ds_string string_trim(ds_string* str, const size_t start, size_t end)
{
	if (str == NULL || *str == NULL || end < start || end > strlen(*str)) return NULL;

	ds_string copy = string_create(*str);
	string_change(str, string_cut(&copy, start, end));

	return copy;
}

ds_string string_cut(ds_string* str, const size_t start, const size_t end)
{
	if (str == NULL || *str == NULL || end < start || end > strlen(*str)) return NULL;	

	size_t len = strlen(*str),
		   newlen;

	if (start == end) newlen = 0;
	else newlen = len-(end-start);

	ds_string cut = string_substring(*str, start, end);

	memmove(*str+start, *str+end, sizeof(char)*(len-end));
	*str = realloc(*str, sizeof(char)*(newlen+1));
	(*str)[newlen] = '\0';

	return cut;
}


int string_replace(ds_string* dst, ds_string src, const size_t start, const size_t end)
{
	string_destroy(string_cut(dst, start, end));
	return string_insert(dst, src, start);
}

int string_replace_all(ds_string* dst, ds_string key, ds_string src)
{
	if (dst == NULL || *dst == NULL || key == NULL || src == NULL) return DASH_NULLARG;

	size_t dstlength = strlen(*dst),
		   keylength = strlen(key),
		   srclength = strlen(src);

	size_t pos = -srclength;
	while (( pos = string_find(*dst, key, pos+srclength, dstlength=strlen(*dst)) ) != dstlength)
		string_replace(dst, src, pos, pos+keylength);

	return DASH_OK;
}

int string_to_lower(ds_string str)
{
	if (str == NULL) return DASH_NULLARG;

	size_t len = strlen(str);
	for (size_t i = 0; i < len; i++)
		if (str[i] >= 'A' && str[i] <= 'Z') str[i] += 'a'-'A';

	return DASH_OK;
}

int string_to_upper(ds_string str)
{
	if (str == NULL) return DASH_NULLARG;

	size_t len = strlen(str);
	for (size_t i = 0; i < len; i++)
		if (str[i] >= 'a' && str[i] <= 'z') str[i] -= 'a'-'A';

	return DASH_OK;
}

int string_change(ds_string* dst, ds_string src)
{
	if (dst == NULL) return DASH_NULLARG;

	string_destroy(*dst);
	*dst = src;

	return DASH_OK;
}

_Bool string_equals(ds_string str1, ds_string str2)
{
	if (str1 == NULL || str2 == NULL) return 0;

	return strcmp(str1, str2) == 0;
}

size_t string_length(ds_string str)
{
	if (str == NULL) return 0;
	return strlen(str);
}

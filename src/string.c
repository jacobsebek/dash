#include "dash/string.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define DS_STRPNULL(strp) ((strp) == NULL || *(strp) == NULL)

ds_string string_create(char* src)
{
	if (src == NULL) src = "";

	ds_string str = malloc((strlen(src)+1)*sizeof(char));
	strcpy(str, src);
	return str;
}

ds_string string_create_c(char c)
{
	char str[2] = {c, '\0'};
	return string_create(str);
}

int string_destroy(ds_string* str)
{
	if (DS_STRPNULL(str)) return DASH_NULLARG;
	free(*str);
	return DASH_OK;
}

int string_insert(ds_string* dst, const ds_string src, const size_t pos)
{
	if (DS_STRPNULL(dst) || src == NULL) return DASH_NULLARG;

	size_t dstlen = strlen(*dst), 
		 srclen = strlen(src);

	if (pos > dstlen) return DASH_MEMFAULT;

	size_t newlen = dstlen+srclen;

	ds_string new = malloc( (newlen+1)*sizeof(char) );

	for (size_t i = 0; i < newlen; i++) {
		if (i < pos) new[i] = (*dst)[i];
		else if (i-pos < srclen) new[i] = src[i-pos];
		else new[i] = (*dst)[i-srclen];
	}
	new[newlen] = '\0';

	string_destroy(dst);
	*dst = new;

	return DASH_OK;
}

int string_append(ds_string* dst, const ds_string src) // [ABC0] + [1230] = [ABC0---], [ABC1230]
{
	if (DS_STRPNULL(dst) || src == NULL) return DASH_NULLARG;

	size_t dstlen = strlen(*dst), 
		   srclen = strlen(src);
	size_t newlen = dstlen+srclen;

	*dst = realloc(*dst, (newlen+1)*sizeof(char));
	memcpy(*dst+dstlen, src, srclen*sizeof(char));
	(*dst)[newlen] = '\0';
	
	return DASH_OK;
}

int ds_string_prepend(ds_string* dst, const ds_string src)
{
	if (DS_STRPNULL(dst) || src == NULL) return DASH_NULLARG;

	size_t dstlen = strlen(*dst), 
		 srclen = strlen(src);
	size_t newlen = dstlen+srclen;

	*dst = realloc(*dst, (newlen+1)*sizeof(char));
	memmove(*dst+srclen, *dst, dstlen*sizeof(char));
	memcpy(*dst, src, srclen*sizeof(char));
	(*dst)[newlen] = '\0';

	return DASH_OK;
}

size_t string_find(const ds_string str, const ds_string key, const size_t start, const size_t end)
{
	if (end < start || end >= strlen(str) ||
		str == NULL || key == NULL) return end+1;

	size_t keylength = strlen(key);

	size_t matches = 0;
	for (size_t i = start; i <= end; i++)
		if (str[i] == key[matches]) {
			if (++matches == keylength) return i-(keylength-1);
		} else matches = 0;

	return end+1;
}

ds_string string_substring(const ds_string str, const size_t start, const size_t end) //TODO:Better imp
{
	if (str == NULL || end < start || end >= strlen(str)) return NULL;

	size_t newlen = end-start+1;
	ds_string new = malloc( (newlen+1)*sizeof(char) );
	for (size_t i = 0; i < newlen; i++)
		new[i] = str[start+i];

	new[newlen] = '\0';
	return new;
}

ds_string string_trim(ds_string* str, const size_t start, const size_t end)
{
	if (DS_STRPNULL(str) || end < start || end >= strlen(*str)) return NULL;

	ds_string copy;
	if (string_copy(&copy, *str) != DASH_OK) return NULL;

	string_destroy(str);
	*str = string_cut(&copy, start, end);

	return copy;
}

ds_string string_cut(ds_string* str, const size_t start, const size_t end)
{
	if (DS_STRPNULL(str) || end < start || end >= strlen(*str)) return NULL;	

	size_t newlen = strlen(*str)-(end-start+1);

	ds_string new = malloc( (newlen+1)*sizeof(char) );
	ds_string cut = string_substring(*str, start, end);

	for (size_t i = 0; i < newlen; i++) {
		if (i < start) new[i] = (*str)[i];
		else new[i] = (*str)[i+(end-start+1)];
	}
	new[newlen] = '\0';

	string_destroy(str);
	*str = new;

	return cut;
}

int string_replace(ds_string* dst, const ds_string src, const size_t start, const size_t end)
{
	if (DS_STRPNULL(dst) || src == NULL) return DASH_NULLARG;
	if (end < start || end >= strlen(*dst)) return DASH_MEMFAULT;

	size_t dstlength = strlen(*dst), 
		 srclength = strlen(src);

	if (end < start || start < 0 || end >= dstlength) return DASH_MEMFAULT;

	size_t newlength = dstlength+srclength-(end-start+1);

	ds_string new = malloc( (newlength+1)*sizeof(char) );

	for (size_t i = 0; i < newlength; i++) {
		if (i < start) new[i] = (*dst)[i];
		else if (i-start < srclength) new[i] = src[i-start];
		else new[i] = (*dst)[i-srclength+(end-start+1)];
	}
	new[newlength] = '\0';

	string_destroy(dst);
	*dst = new;

	return DASH_OK;
}

int string_replace_all(ds_string* dst, const ds_string key, const ds_string src)
{
	if (DS_STRPNULL(dst) || key == NULL || src == NULL) return DASH_NULLARG;

	size_t dstlength = strlen(*dst),
		 keylength = strlen(key),
		 srclength = strlen(src);

	size_t pos = -srclength;
	while (( pos = string_find(*dst, key, pos+srclength, (dstlength=strlen(*dst))-1) ) != dstlength)
		string_replace(dst, src, pos, pos+keylength-1);

	return DASH_OK;
}

int string_to_lower(ds_string* str)
{
	if (DS_STRPNULL(str)) return DASH_NULLARG;

	size_t len = strlen(*str);
	for (size_t i = 0; i < len; i++)
		if ((*str)[i] >= 'A' && (*str)[i] <= 'Z') (*str)[i] += 'a'-'A';

	return DASH_OK;
}

int string_to_upper(ds_string* str)
{
	if (DS_STRPNULL(str)) return DASH_NULLARG;

	size_t len = strlen(*str);
	for (size_t i = 0; i < len; i++)
		if ((*str)[i] >= 'a' && (*str)[i] <= 'z') (*str)[i] -= 'a'-'A';

	return DASH_OK;
}

int string_copy(ds_string* dst, const ds_string src)
{
	if (DS_STRPNULL(dst) || src == NULL) return DASH_NULLARG;

	ds_string new = malloc( (strlen(src)+1)*sizeof(char) );

	strcpy(new, src);

	string_destroy(dst);
	*dst = new;

	return DASH_OK;
}

int string_move(ds_string* dst, const ds_string src)
{
	if (DS_STRPNULL(dst) || src == NULL) return DASH_NULLARG;

	if (*dst != NULL && string_destroy(dst) != DASH_OK) return DASH_MEMFAULT;

	*dst = src;
	return DASH_OK;
}

_Bool string_equals(const ds_string str1, const ds_string str2)
{
	if (str1 == NULL || str2 == NULL) return DASH_NULLARG;

	size_t len1 = strlen(str1);
	if (len1 != strlen(str2)) return 0;

	for (size_t i = 0; i < len1; i++)
		if (str1[i] != str2[i]) return 0;

	return 1;
}

int ds_stringrint(const ds_string str)
{
	if (str == NULL) return DASH_NULLARG;
	return printf("> %s\n", str) ? DASH_OK : DASH_MEMFAULT;
}

int ds_stringrint_dec(const ds_string str)
{
	if (str == NULL) return DASH_NULLARG;
	printf("> ");
	for (size_t i = 0; i < strlen(str); i++)
		if (!printf("%d;", str[i])) return DASH_MEMFAULT;
	printf("\n");

	return DASH_OK;
}

size_t string_length(const ds_string str)
{
	if (str == NULL) return DASH_NULLARG;
	return strlen(str);
}

#undef DS_STRPNULL

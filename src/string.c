#include "dash/string.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

string_p string_create(string_p src)
{
	if (src == NULL) src = "";

	string_p str = malloc((strlen(src)+1)*sizeof(char));
	strcpy(str, src);
	return str;
}

string_p string_create_c(char c)
{
	char str[2] = {c, '\0'};
	return string_create(str);
}

int string_destroy(string_p* str)
{
	if (str == NULL) return DASH_NULLARG;
	free(*str);
	return DASH_OK;
}

int string_insert(string_p* dst, const string_p src, const uint pos)
{
	if (dst == NULL || src == NULL) return DASH_NULLARG;

	uint dstlen = strlen(*dst), 
		 srclen = strlen(src);

	if (pos > dstlen) return DASH_MEMFAULT;

	uint newlen = dstlen+srclen;

	string_p new = malloc( (newlen+1)*sizeof(char) );

	for (uint i = 0; i < newlen; i++) {
		if (i < pos) new[i] = (*dst)[i];
		else if (i-pos < srclen) new[i] = src[i-pos];
		else new[i] = (*dst)[i-srclen];
	}
	new[newlen] = '\0';

	string_destroy(dst);
	*dst = new;

	return DASH_OK;
}

int string_append(string_p* dst, const string_p src) // [ABC0] + [1230] = [ABC0---], [ABC1230]
{
	if (dst == NULL || src == NULL) return DASH_NULLARG;

	uint dstlen = strlen(*dst), 
		 srclen = strlen(src);
	uint newlen = dstlen+srclen;

	*dst = realloc(*dst, (newlen+1)*sizeof(char));
	memcpy(*dst+dstlen, src, srclen*sizeof(char));
	(*dst)[newlen] = '\0';
	
	return DASH_OK;
}

int string_prepend(string_p* dst, const string_p src)
{
	if (dst == NULL || src == NULL) return DASH_NULLARG;

	uint dstlen = strlen(*dst), 
		 srclen = strlen(src);
	uint newlen = dstlen+srclen;

	*dst = realloc(*dst, (newlen+1)*sizeof(char));
	memmove(*dst+srclen, *dst, dstlen*sizeof(char));
	memcpy(*dst, src, srclen*sizeof(char));
	(*dst)[newlen] = '\0';

	return DASH_OK;
}

uint string_find(const string_p str, const string_p key, const uint start, const uint end)
{
	if (end < start || end >= strlen(str) ||
		str == NULL || key == NULL) return end+1;

	uint keylength = strlen(key);

	uint matches = 0;
	for (uint i = start; i <= end; i++)
		if (str[i] == key[matches]) {
			if (++matches == keylength) return i-(keylength-1);
		} else matches = 0;

	return end+1;
}

string_p string_substring(string_p* str, const uint start, const uint end) //TODO:Better imp
{
	if (str == NULL || end < start || end >= strlen(*str)) return NULL;

	uint newlen = end-start+1;
	string_p new = malloc( (newlen+1)*sizeof(char) );
	for (uint i = 0; i < newlen; i++)
		new[i] = (*str)[start+i];

	new[newlen] = '\0';
	return new;
}

int string_trim(string_p* str, const uint start, const uint end)
{
	if (str == NULL) return DASH_NULLARG;
	if (end < start || end >= strlen(*str)) return DASH_MEMFAULT;

	string_destroy(str);
	*str = string_substring(str, start, end);

	return DASH_OK;
}

string_p string_cut(string_p* str, const uint start, const uint end)
{
	if (str == NULL || end < start || end >= strlen(*str)) return NULL;	

	uint newlen = strlen(*str)-(end-start+1);

	string_p new = malloc( (newlen+1)*sizeof(char) );
	string_p cut = string_substring(str, start, end);

	for (uint i = 0; i < newlen; i++) {
		if (i < start) new[i] = (*str)[i];
		else new[i] = (*str)[i+(end-start+1)];
	}
	new[newlen] = '\0';

	string_destroy(str);
	*str = new;

	return cut;
}

int string_replace(string_p* dst, const string_p src, const uint start, const uint end)
{
	if (dst == NULL || src == NULL) return DASH_NULLARG;
	if (end < start || end >= strlen(*dst)) return DASH_MEMFAULT;

	uint dstlength = strlen(*dst), 
		 srclength = strlen(src);

	if (end < start || start < 0 || end >= dstlength) return DASH_MEMFAULT;

	uint newlength = dstlength+srclength-(end-start+1);

	string_p new = malloc( (newlength+1)*sizeof(char) );

	for (uint i = 0; i < newlength; i++) {
		if (i < start) new[i] = (*dst)[i];
		else if (i-start < srclength) new[i] = src[i-start];
		else new[i] = (*dst)[i-srclength+(end-start+1)];
	}
	new[newlength] = '\0';

	string_destroy(dst);
	*dst = new;

	return DASH_OK;
}

int string_replace_all(string_p* dst, const string_p key, const string_p src)
{
	if (dst == NULL || key == NULL || src == NULL) return DASH_NULLARG;

	uint dstlength = strlen(*dst),
		 keylength = strlen(key),
		 srclength = strlen(src);

	uint pos = -srclength;
	while (( pos = string_find(*dst, key, pos+srclength, (dstlength=strlen(*dst))-1) ) != dstlength)
		string_replace(dst, src, pos, pos+keylength-1);

	return DASH_OK;
}

int string_to_lower(string_p* str)
{
	if (str == NULL) return DASH_NULLARG;

	uint len = strlen(*str);
	for (uint i = 0; i < len; i++)
		if ((*str)[i] >= 'A' && (*str)[i] <= 'Z') (*str)[i] += 'a'-'A';

	return DASH_OK;
}

int string_to_upper(string_p* str)
{
	if (str == NULL) return DASH_NULLARG;

	uint len = strlen(*str);
	for (uint i = 0; i < len; i++)
		if ((*str)[i] >= 'a' && (*str)[i] <= 'z') (*str)[i] -= 'a'-'A';

	return DASH_OK;
}

int string_copy(string_p* dst, const string_p src)
{
	if (src == NULL) return DASH_NULLARG;

	string_p new = malloc( (strlen(src)+1)*sizeof(char) );

	strcpy(new, src);

	string_destroy(dst);
	*dst = new;

	return DASH_OK;
}

int string_move(string_p* dst, const string_p src)
{
	if (dst == NULL || src == NULL) return DASH_NULLARG;

	if (*dst != NULL && string_destroy(dst) != DASH_OK) return DASH_MEMFAULT;

	*dst = src;
	return DASH_OK;
}

bool string_equals(const string_p str1, const string_p str2)
{
	if (str1 == NULL || str2 == NULL) return DASH_NULLARG;

	uint len1 = strlen(str1);
	if (len1 != strlen(str2)) return 0;

	for (uint i = 0; i < len1; i++)
		if (str1[i] != str2[i]) return 0;

	return 1;
}

int string_print(const string_p str)
{
	if (str == NULL) return DASH_NULLARG;
	return printf("> %s\n", str) ? DASH_OK : DASH_MEMFAULT;
}

int string_print_dec(const string_p str)
{
	if (str == NULL) return DASH_NULLARG;
	printf("> ");
	for (uint i = 0; i < strlen(str); i++)
		if (!printf("%d;", str[i])) return DASH_MEMFAULT;
	printf("\n");

	return DASH_OK;
}

uint string_length(const string_p str)
{
	if (str == NULL) return DASH_NULLARG;
	return strlen(str);
}

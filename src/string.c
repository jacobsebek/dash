#include "dash/string.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

string string_create(string src)
{
	if (src == NULL) src = "";

	string str = (string)malloc((strlen(src)+1)*sizeof(char));
	strcpy(str, src);
	return str;
}

string string_create_c(char c)
{
	char str[2] = {c, '\0'};
	return string_create(str);
}

int string_destroy(string str)
{
	if (str == NULL) return DASH_NULLARG;
	free(str);
	return DASH_OK;
}

int string_insert(string* dst, string src, uint pos)
{
	if (dst == NULL || src == NULL) return DASH_NULLARG;

	uint dstlen = strlen(*dst), 
		 srclen = strlen(src);

	if (pos > dstlen) return DASH_MEMFAULT;

	uint newlen = dstlen+srclen;

	string new = (string)malloc( (newlen+1)*sizeof(char) );

	for (uint i = 0; i < newlen; i++) {
		if (i < pos) new[i] = (*dst)[i];
		else if (i-pos < srclen) new[i] = src[i-pos];
		else new[i] = (*dst)[i-srclen];
	}
	new[newlen] = '\0';

	string_destroy(*dst);
	*dst = new;

	return DASH_OK;
}

int string_append(string* dst, string src)
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

int string_prepend(string* dst, string src)//TODO:possible own better implementation
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

uint string_find(string str, string key, uint start, uint end)
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

string string_substring(string str, uint start, uint end)
{
	if (str == NULL || end < start || end >= strlen(str)) return NULL;

	uint newlen = end-start+1;
	string new = (string)malloc( (newlen+1)*sizeof(char) );
	for (uint i = 0; i < newlen; i++)
		new[i] = str[start+i];

	new[newlen] = '\0';
	return new;
}

int string_trim(string* str, uint start, uint end)
{
	if (str == NULL) return DASH_NULLARG;
	if (end < start || end >= strlen(*str)) return DASH_MEMFAULT;

	string_destroy(*str);
	*str = string_substring(*str, start, end);

	return DASH_OK;
}

string string_cut(string* str, uint start, uint end)
{
	if (str == NULL || end < start || end >= strlen(*str)) return NULL;	

	uint newlen = strlen(*str)-(end-start+1);

	string new = (string)malloc( (newlen+1)*sizeof(char) );
	string cut = string_substring(*str, start, end);

	for (uint i = 0; i < newlen; i++) {
		if (i < start) new[i] = (*str)[i];
		else new[i] = (*str)[i+(end-start+1)];
	}
	new[newlen] = '\0';

	string_destroy(*str);
	*str = new;

	return cut;
}

int string_replace(string* dst, string src, uint start, uint end)
{
	if (dst == NULL || src == NULL) return DASH_NULLARG;
	if (end < start || end >= strlen(*dst)) return DASH_MEMFAULT;

	uint dstlength = strlen(*dst), 
		srclength = strlen(src);

	if (end < start || start < 0 || end >= dstlength) return DASH_MEMFAULT;

	uint newlength = dstlength+srclength-(end-start+1);

	string new = (string)malloc( (newlength+1)*sizeof(char) );

	for (uint i = 0; i < newlength; i++) {
		if (i < start) new[i] = (*dst)[i];
		else if (i-start < srclength) new[i] = src[i-start];
		else new[i] = (*dst)[i-srclength+(end-start+1)];
	}
	new[newlength] = '\0';

	string_destroy(*dst);
	*dst = new;

	return DASH_OK;
}

int string_replace_all(string* dst, string key, string src)
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

int string_to_lower(string* str)
{
	if (str == NULL) return DASH_NULLARG;

	uint len = strlen(*str);
	for (uint i = 0; i < len; i++)
		if ((*str)[i] >= 'A' && (*str)[i] <= 'Z') (*str)[i] += 'a'-'A';

	return DASH_OK;
}

int string_to_upper(string* str)
{
	if (str == NULL) return DASH_NULLARG;

	uint len = strlen(*str);
	for (uint i = 0; i < len; i++)
		if ((*str)[i] >= 'a' && (*str)[i] <= 'z') (*str)[i] -= 'a'-'A';

	return DASH_OK;
}

int string_set(string* dst, string src)
{
	if (dst == NULL || src == NULL) return DASH_NULLARG;

	string new = (string)malloc( (strlen(src)+1)*sizeof(char) );

	strcpy(new, src);

	string_destroy(*dst);
	*dst = new;

	return DASH_OK;
}

bool string_equals(string str1, string str2)
{
	if (str1 == NULL || str2 == NULL) return DASH_NULLARG;

	uint len1 = strlen(str1);
	if (len1 != strlen(str2)) return 0;

	for (uint i = 0; i < len1; i++)
		if (str1[i] != str2[i]) return 0;

	return 1;
}

int string_print(string str)
{
	if (str == NULL) return DASH_NULLARG;
	return printf("[\"%s\"]\n", str) ? DASH_OK : DASH_MEMFAULT;
}

int string_print_dec(string str)
{
	if (str == NULL) return DASH_NULLARG;
	printf("[\"");
	for (uint i = 0; i < strlen(str); i++)
		if (!printf("%d;", str[i])) return DASH_MEMFAULT;
	printf("\"]\n");

	return DASH_OK;
}

uint string_length(string str)
{
	if (str == NULL) return DASH_NULLARG;
	return strlen(str);
}

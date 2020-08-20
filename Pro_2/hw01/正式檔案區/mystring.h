#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#pragma once


int32_t mystrcmp(const char *s, const char *c);
char *mystrchr(const char *s, int32_t c);
char *mystrrchr(const char *s, int32_t c);
size_t mystrspn(const char *s, const char *accept);
size_t mystrcspn(const char *s, const char *reject);
char *mystrpbrk(const char*s, const char *accept);
char *mystrstr(const char *haystack, const char *needle);
char *mystrtok(char *str, const char *delim);



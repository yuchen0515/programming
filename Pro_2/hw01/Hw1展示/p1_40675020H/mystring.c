#include "mystring.h"

char *mystrchr(const char *s, int c){
	do{
		if (*s == c)
			return (char *)s;
	} while (*s ++);
	return NULL;
}

char *mystrrchr(const char *s, int c){
	char *ret = NULL;
	do{
		if (*s == c)
			ret = (char *)s;
	} while (*s ++);
	return ret;
}

size_t mystrspn(const char *s, const char *accept){
	size_t cnt = 0;
	char *c = NULL;
	while (*s){
		for (c=(char *)accept; *c!=0; c++){
			if (*s == *c){
				cnt ++;
				break;
			}
		}
		if (*c == 0)
			return cnt;
		s ++;
	}
	return cnt;
}

size_t mystrcspn(const char *s, const char *reject){
	size_t cnt = 0;
	char *c = NULL;
	while (*s){
		for (c=(char *)reject; *c!=0; c++){
			if (*s == *c)
				return cnt;
		}
		if (*c == 0)
			cnt ++;
		s ++;
	}
	return cnt;
}

char *mystrpbrk(const char *s, const char *accept){
	while (*s){
		for (char *c=(char *)accept; *c!=0; c++){
			if (*s == *c)
				return (char *)s;
		}
		s ++;
	}
	return NULL;
}

char *mystrstr(const char *haystack, const char *needle){
	size_t pos = 0;
	if (*needle == 0)
		return (char *)haystack;
	while (*haystack){
		while (*(haystack+pos) == *(needle+pos)){
			if (*(needle+pos+1) == 0)
				return (char *)haystack;
			pos ++;
		}
		pos = 0;
		haystack ++;
	}
	return NULL;
}

char *mystrtok(char *str, const char *delim){
	static char *last = NULL;
	if (str == NULL)
		str = last;
	str += mystrspn(str, delim);
	if (*str == 0)
		return NULL;
	char *token = str;
	str = mystrpbrk(token, delim);
	if (str == NULL)
		last = mystrchr(token, 0);
	else{
		*str = 0;
		last = str + 1;
	}
	return token;
}
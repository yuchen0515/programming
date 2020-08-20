#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void catstr(char str[], char pt[]);
int32_t pat_verify(char text[], char pat[]);
int32_t mark(char c, char pattern);
char* readget(char *str, int32_t size, FILE* stream, int32_t choice);
void del_space(char *str);

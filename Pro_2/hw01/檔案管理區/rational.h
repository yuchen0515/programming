#include <stdint.h>
#include <stdio.h>

#pragma once

void swap(int32_t *a, int32_t *b);
int32_t gcd(int32_t a, int32_t b);

struct rational{
	int32_t num;
	int32_t don;
};
int32_t rational_neg(const struct rational r1);
void rational_abs(struct rational *r);

int32_t rational_set(struct rational *r, int32_t p, int32_t q);
// return -1 if invalid; other wise, return 0.

int32_t rational_print(const struct rational r);
// in the form of (p,q)


void rational_add(struct rational *r, const struct rational r1, const struct rational r2);
// r = r1 + r2

void rational_sub(struct rational *r, const struct rational r1, const struct rational r2);
// r = r1 - r2

void rational_mul(struct rational *r, const struct rational r1, const struct rational r2);
// r = r1 * r2

void rational_div(struct rational *r, const struct rational r1, const struct rational r2);
// r = r1 / r2


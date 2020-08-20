#include <stdint.h>

#pragma once

struct rational {
	int32_t up;
	int32_t dw;
};

int rational_set( struct rational *r, int32_t p, int32_t q);
// return -1 if invalid; otherwise , return 0.
int rational_print( const struct rational r);
// in the form of (p,q)
void rational_add( struct rational *r, const struct rational r1, const struct rational r2);
// r = r1 + r2
void rational_sub( struct rational *r, const struct rational r1, const struct rational r2);
// r = r1 - r2
void rational_mul( struct rational *r, const struct rational r1, const struct rational r2);
// r = r1 * r2
void rational_div( struct rational *r, const struct rational r1, const struct rational r2);
// r = r1 / r2
int32_t gcd(int32_t a, int32_t b);

int32_t lcm(int32_t a, int32_t b);
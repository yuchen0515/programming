#include "rational.h"
#include <stdint.h>
#include <stdio.h>

int rational_set( struct rational *r, int32_t p, int32_t q)
{
	if(q == 0)
	{
		printf("you have invalid rational set\n");
		return -1;
	}
	int32_t tmp = gcd(p, q);
	r->up = p / tmp;
	r->dw = q / tmp;
	return 0;
}
// return -1 if invalid; otherwise , return 0.

int rational_print( const struct rational r)
{
	printf("(%d,%d)\n", r.up, r.dw);
}
// in the form of (p,q)

void rational_add( struct rational *r, const struct rational r1, const struct rational r2)
{
	int32_t dtmp, utmp;
	dtmp = lcm(r1.dw, r2.dw);
	utmp = (dtmp / r1.dw * r1.up) + (dtmp / r2.dw * r2.up);
	r -> up = utmp / gcd(utmp, dtmp);
	r -> dw = dtmp / gcd(utmp, dtmp);
	return;
}
// r = r1 + r2

void rational_sub( struct rational *r, const struct rational r1, const struct rational r2)
{
	int32_t dtmp, utmp;
	dtmp = lcm(r1.dw, r2.dw);
	utmp = (dtmp / r1.dw * r1.up) - (dtmp / r2.dw * r2.up);
	r -> up = utmp / gcd(utmp, dtmp);
	r -> dw = dtmp / gcd(utmp, dtmp);
	return;
}
// r = r1 - r2

void rational_mul( struct rational *r, const struct rational r1, const struct rational r2)
{
	int32_t utmp = r1.up * r2.up;
	int32_t dtmp = r1.dw * r2.dw;
	int32_t tmp = gcd(utmp, dtmp);
	r -> up = utmp / tmp;
	r -> dw = dtmp / tmp;
	return;
}
// r = r1 * r2

void rational_div( struct rational *r, const struct rational r1, const struct rational r2)
{
	if(r2.up == 0)
	{
		printf("you can't divide 0\n");
		exit(1);
	}
	int32_t utmp = r1.up * r2.dw;
	int32_t dtmp = r1.dw * r2.up;
	int32_t tmp = gcd(utmp, dtmp);
	r -> up = utmp / tmp;
	r -> dw = dtmp / tmp;
	return;
}
// r = r1 / r2

int32_t gcd(int32_t a, int32_t b)
{
	if(b)
		while((a %= b) && (b %= a));
	return a + b;
}

int32_t lcm(int32_t a, int32_t b)
{
	int32_t tmp = gcd(a, b);
	if(tmp < 0)
		tmp = -tmp;
	return a / tmp * b;
}
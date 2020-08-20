#include <stdio.h>
#include "hw0505_header.h"


//輾轉相除法加強
int32_t gcd(int32_t o, int32_t t){
	if (t>o) return gcd(t,o);
	if (t==1 || o==1) return 1;
	if (t==o) return t;
	if ((!o&1) && (!t&1)) return gcd(o>>1,t>>1);
	if ((!o&1) && (t&1)) return gcd(o>>1,t);
	if ((o&1) && (!t&1)) return gcd(o,t>>1);
	return gcd(o-t,t);
}

//分子分母同除函式(特別注意gcd不可使用在負數或0)
void modify(int32_t *e, int32_t *f){
	int32_t neg = 1, neg2 = 1;
	if (*e <0) neg=-1;
	if (*f <0) neg2=-1;
	*e = *e * neg;
	*f = *f * neg2;
	int32_t k = gcd(*e, *f);
	if ((*e % k ==0) && (*f % k ==0)){
		*e = *e / k;
		*f = *f / k;
	}
	*e = *e * neg;
	*f = *f * neg2;
}

//加法
void add(int32_t a, int32_t b, int32_t c, int32_t d, int32_t *e, int32_t *f){
	*e = a*d + b*c;
	*f = b*d;
	if (*e!=0 && *f!=0) modify(e,f);
	if (*e<0 && *f<0){
		*e *= -1;
		*f *= -1;
	}
}

//減法
void sub(int32_t a, int32_t b, int32_t c, int32_t d, int32_t *e, int32_t *f){
	*e = a*d - b*c;
	*f = b*d;
	if (*e!=0 && *f!=0) modify(e,f);
	if (*e<0 && *f<0){
		*e *= -1;
		*f *= -1;
	}
}

//乘法
void mul(int32_t a, int32_t b, int32_t c, int32_t d, int32_t *e, int32_t *f){
	*e = a*c;
	*f = b*d;
	if (*e!=0 && *f!=0) modify(e,f);
	if (*e==0) *f=1;
	if (*e>=0 && *f<0){
		*e *= -1;
		*f *= -1;
	}
}

//除法
void div(int32_t a, int32_t b, int32_t c, int32_t d, int32_t *e, int32_t *f){
	*e = a*d;
	*f = b*c;
	if (*e!=0 && *f!=0) modify(e,f);
	if (*e==0) *f=1;
	if (*e>=0 && *f<0){
		*e *= -1;
		*f *= -1;
	}
}

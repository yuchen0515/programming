#include "hw0405_header.h"

int32_t inverse(int32_t mo, int32_t num){
	
	int32_t upper = 0;

	if (mo==1) return -1;	//模數為1，不存在模倒數
	if ( gcd(mo, num) !=1 ) return -1;	//兩個不是互質，則不存在模倒數
	
	int32_t i = 0;
	while (1){
		upper = 1 + mo * i++;	
		if ((upper/num) > mo) return -1;	//模倒數不大於模
		if (gcd(upper, num) == num) return upper/num;	//分子分母的公因數為分母，則可以整除
	}

	//到這都還沒回傳，表示沒有模倒數
	return -1;

}

//輾轉相除法加強版
int32_t gcd(int32_t a, int32_t b){

	if (a == b)	return a;
	if (b > a)	return gcd(b, a);	//讓gcd參數永遠a>=b

	if (!a&1 && !b&1) return gcd(a>>1, b>>1);	//ab都偶數，則都除以二
	else if (!a&1 && b&1) return gcd(a>>1, b);	//a偶數，b奇數，回傳gcd(a/2,b)
	else if (a&1 && !b&1) return gcd(a, b>>1);	//a奇數，b偶數，回傳gcd(a,b/2)
	else return gcd(b, a-b);	//ab都奇數，根據更相減損術，回傳gcd(b,a-b)

}

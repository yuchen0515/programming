#include <stdio.h>
#include <stdint.h>
#include "hw0505_header.h"		//引入自製標頭檔，以便使用add,sub,mul,div函式

int main(){

	int32_t au= 0, al = 0, bu = 0, bl = 0;
	int32_t anu = 0, anl = 0;
	int32_t *ptr_u= &anu, *ptr_l = &anl;	//利用指標副函式才有辦法改到這裡的數值

	//提示使用者輸入，分母為0重新輸入
	printf("Please enter 1st rational number: ");
	scanf("%d %d", &au,&al);
	while (al==0){
		printf("Input error! denominator don't be a zero\n");
		printf("Please enter 1st rational number: ");
		scanf("%d %d", &au,&al);
	}

	//提示使用者輸入，分母為0重新輸入
	printf("Please enter 2st rational number: ");
	scanf("%d %d", &bu,&bl);
	while (bl==0){
		printf("Input error! denominator don't be a zero\n");
		printf("Please enter 2st rational number: ");
		scanf("%d %d", &bu,&bl);
	}
	//單個分子為0時，該分子分母可不理會，用另個輸入的數值當作答案
	//分子都不為0就呼叫add函式幫助計算
	int32_t neg = 1;
	if (au==0){
		anu = bu*neg;
		anl = bl;
		neg = -1;
	}else if (bu==0){
		anu = au;
		anl = al;
	}else{
		add(au,al,bu,bl,ptr_u,ptr_l);
	}
	//分子計算後還是0，就把分母化成0/1的形式(最簡)
	if (anu==0) anl = 1;
	else if (anu>1||anu<-1) modify(ptr_u,ptr_l);	//不是0，就幫忙化到最簡 (可能使用者輸入0/2 + 4/8)
	printf("%d/%d + %d/%d = %d/%d\n",au,al,bu,bl,anu,anl);


	//分子為0的時候要特別處理，否則gcd會出問題，若函式都改用int32_t會比較好處理
	if (au==0){
		anu = bu*neg;
		anl = bl;
	}else if (bu==0){
		anu = au;
		anl = al;
	}else{
		sub(au,al,bu,bl,ptr_u,ptr_l);
	}
	//分子計算後還是0，就把分母化成0/1的形式(最簡)
	if (anu==0) anl = 1;
	else if (anu>1||anu<-1) modify(ptr_u,ptr_l);	//不是0，就幫忙化到最簡 (可能使用者輸入0/2 + 4/8)
	printf("%d/%d - %d/%d = %d/%d\n",au,al,bu,bl,anu,anl);


	//乘法
	mul(au,al,bu,bl,ptr_u,ptr_l);
	printf("%d/%d * %d/%d = %d/%d\n",au,al,bu,bl,anu,anl);
	

	//除法是乘以倒數，若第二個分數的分子為0，最終分母會為0則不合法
	if (bu==0){
		printf("division don't operate since the denominator is zero\n");
	}else{
		div(au,al,bu,bl,ptr_u,ptr_l);
		printf("%d/%d / %d/%d = %d/%d\n",au,al,bu,bl,anu,anl);
	}

	return 0;
}

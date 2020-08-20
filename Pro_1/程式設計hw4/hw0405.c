#include <stdio.h>	//引用標頭檔<stdio.h> 以便標準輸入和輸出
#include <stdint.h>	//引用標頭檔<stdint.h> 以便使用標準整數型態
#include "hw0405_header.h"	//引用自製作的header file

int main(){		//提示主函式的進入點
	
	int32_t mo = 0, num = 0, inv = 0;	//設定變數
	
	//提示輸入模數
	printf("Please enter the modulus: ");
	scanf("%d", &mo);
	//檢查模數是否大於0, 若否則提示使用者重新輸入
	while (!(mo>0)){
		printf("Input error! please enter a number over zero\n");
		printf("Please enter the modulus: ");
		scanf("%d", &mo);
	}

	//提示輸入數字
	printf("Please enter the number: ");
	scanf("%d", &num);
	//檢查數字是否大於0, 若否則提示使用者重新輸入
	while (!(num>0)){
		printf("Input error! please enter a number over zero\n");
		printf("Please enter the modulus: ");
		scanf("%d", &num);
	}

	//呼叫標頭檔hw0405_header.h內的函式
	inv = inverse(mo, num);	//讀inverse的值存進inv內

	//print
	//回傳-1表示模倒數不存在
	if (inv == -1) printf("The modular multiplicative inverse of %d isn't exist\n", num);
	else printf("The modular multiplicative inverse of %d is %d\n", num, inv);
	
	return 0;
}

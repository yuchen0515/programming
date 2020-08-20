#include <stdio.h>			//引入標頭檔<stdio.h>，以便標準輸入和輸出
#include <stdint.h>			//引入標頭檔<stdint.h>，以便使用標準整數型態
#include <stdlib.h>			//引入標頭檔<stdlib.h>，以便使用裡面的abs以及calloc
#include "hw0604test.h"		//引入助教的test.h(用測資)

void reverse(uint8_t temp[], uint8_t size){		//將陣列的數值倒置

	uint8_t tep[size];
	for (int32_t i = 0 ; i < size ; i++) tep[i] = temp[size-1-i];
	for (int32_t i = 0 ; i < size ; i++) temp[i] = tep[i];

}

void multiplication(uint8_t **result, uint8_t *size, uint8_t *x, uint8_t size_x, uint8_t *y, uint8_t size_y){

	//兩條x,y先倒置
	reverse(x, size_x);
	reverse(y, size_y);

	//根據直式乘法，每個都跑(相乘)
	for (int32_t i = 0 ; i < size_x; i++){
		for (int32_t j = 0 ; j < size_y ; j++){
			*((*result)+(i+j)) += (*(x+i)) * (*(y+j));
			*((*result)+(i+j+1)) += *(*result+(i+j))/10;	//大於10就進位
			*(*result+(i+j)) %=10;		//然後原本那位取個位數
		}
	}

}


int main(){		//提示主函數的進入點

	uint8_t pt = 1;		//前面如果是0不輸出，一直到第一個非零的數字出現為止
	uint8_t si = size_x + size_y + 1;	//size相乘後應可到兩個相加的長度，+1長度為以防萬一
	uint8_t *size = &si;
	uint8_t *ptr = calloc(sizeof(uint8_t), *size);	//calloc出一個空間，長度為size
	uint8_t **result = &ptr;
	//指向calloc的指標的指標(其實這是多餘的，但老師副函式放的是雙重指標)

	multiplication(result, size, x, size_x, y, size_y);

	//從最前面輸出到最後面(第0項)
	printf("Result: ");
	for (int32_t i = *size; i>=0; i--){

		if (*(*result+i) !=0) pt=0;
		if (pt) continue;		//還沒印出第一個非0的數就重新跑
		printf("%hhu", *(*result+i));
		if (i==0) puts("");

	}

	return 0;
}

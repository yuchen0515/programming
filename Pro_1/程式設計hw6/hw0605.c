#include <stdio.h>			//引入標頭檔<stdio.h>，以便標準輸入和輸出
#include <stdint.h>			//引入標頭檔<stdint.h>，以便使用標準整數型態
#include <stdlib.h>			//引入標頭檔<stdlib.h>，以便使用裡面的abs以及calloc
#include "hw0605test.h"	//引入助教的test.h(用測資)

void reverse(uint8_t temp[], uint8_t size){		//將陣列的數值倒置

	uint8_t tep[size];		//利用一條陣列存，之後再一次性丟回去才不會被覆蓋到

	for (int32_t i = 0 ; i < size ; i++) tep[i] = *(temp+size-1-i);
	for (int32_t i = 0 ; i < size ; i++) *(temp+i) = tep[i];

}

//	 初始化，原本感覺會用到，不過之後發現好像用不到
void init(uint8_t temp[], uint8_t size){

	for (int32_t i = 0 ; i < size; i++) *(temp+i) = 0 ;
	
}
//


//等同於 組合語言的 jge (>=的判斷)
//比較兩個大數，前者大於等於後面則輸出1，否則為0
uint8_t largequal(uint8_t pre[], uint8_t pre_size, uint8_t last[], uint8_t last_size){

	//先用陣列大小檢查
	if (pre_size > last_size) return 1;
	if (pre_size < last_size) return 0;

	//大小一樣時，從最大跑到最小，當某數大於或小於某方時結果就出來了
	for (int32_t i = pre_size-1; i >= 0 ; i--){

		if (*(pre+i) > *(last+i))	return 1;
		if (*(pre+i) < *(last+i))	return 0;

	}
	return 1;
	
}

//模擬大數剪法
void substract(uint8_t pre[], uint8_t pre_size, uint8_t last[], uint8_t last_size, uint8_t ret[]){

	//拿ret去存，避免改到原本的數值
	for (int32_t i = 0 ; i < pre_size ; i++) *(ret+i) = *(pre+i);

	//全部跑一次
	for (int32_t i = 0 ; i < pre_size ; i++){

		if (i < last_size){

			//因為是用uint，所以要用這樣的判斷先檢查，否則會溢位
			if ((*(ret+i)-*(last+i)) < 0){

				*(ret+i) +=10;	//借位
				*(ret+i) -= *(last+i);
				*(ret+i+1) -=1;	//之所以可以肯定不超出範圍，是因為這邊做減法時，已確定前面大於後面

			}else *(ret+i) -= *(last+i);	//沒有小於0，就直接減

		}
	}
}

//大數與常數的乘法(乘上一個0-9的數)
void multiplication(uint8_t temp[], uint8_t size, uint8_t mul, uint8_t ret[]){

	//直接一條乘過去一邊進位就行了
	for (int32_t i = 0 ;  i < size ; i++){
		
		*(ret+i) += (*(temp+i) * mul);
		*(ret+i+1) += *(ret+i)/10; 
		*(ret+i) %= 10;

	}
	//特別的是存在ret內，以免改到原本的值

}

//計算大數的真實長度
//這邊len不用陣列存，是因為助教輸入的size也已經確定是"uint8_t"不會超出(見hw0605test.h)
uint8_t len(uint8_t ptr[], uint8_t size){

	uint8_t pt = 1, len = 0;

	for (int32_t i = size-1; i>=0;i--){

		if (*(ptr+i) !=0) pt=0;
		if (pt) continue; 
		len++;

	}
	return len;
}

//真正的除法
void division( uint8_t **quotient, uint8_t *quotient_size, uint8_t **remainder, uint8_t *remainder_size, uint8_t *x, uint8_t size_x, uint8_t *y, uint8_t size_y){

	//先倒置過來，方便計算
	reverse(x, size_x);
	reverse(y, size_y);

	//如果除數大於被除數，就無法除，餘數就等於被除數
	if (size_x < size_y){
		for (int32_t i = 0 ; i < size_x; i++) *(*remainder+i) = *(x+i);
		return;
	}

	//把remainder當儲存減後數字的地方
	for (int32_t i = size_x-size_y ; i < size_x; i++){
		*(*remainder+(i-(size_x-size_y))) = *(x+i);
	}


	//從前往後，商數最大位置應在size_x - size_y的地方
	for (int32_t i = size_x-size_y ; i>=0; i--){

		//長除法就是0~9都試一次，試到最靠近的那一個(卻又不大於原本的數)
		for (int32_t j = 9 ; j>=0 ; j--){

			uint8_t *ptr = calloc(sizeof(uint8_t), 	size_y+1);
			multiplication(y, size_y, j, ptr);
			//先試乘

			uint8_t mul_len = len(ptr, size_y+1);
			uint8_t rem_len = len(*remainder, *remainder_size);
			
			//看原本的數有沒有大於等於，有的話就是那一個(因為從9跑到0)
			if (largequal(*remainder, rem_len, ptr, mul_len)){

				*(*quotient+i) = j;
				uint8_t *men_ptr = calloc(sizeof(uint8_t), size_y+1);
				substract(*remainder, rem_len, ptr, mul_len, men_ptr); //減下去
				uint8_t sub_len = len(men_ptr, size_y+1);

				if (i!=0){	//如果不是最後一個，就補位
					for (int32_t p = sub_len-1 ; p >= 0 ; p--) *(men_ptr+p+1) = *(men_ptr+p);
					*(men_ptr) = *(x+i-1);
				}

				//把算完的餘數丟回給remainder
				for (int32_t p = 0 ; p < size_y+1; p++) *(*remainder+p) = *(men_ptr+p);

				//其中一個商數結束，i--繼續跑
				break;
				
			}
		}
	}
}

int main(){

	uint8_t si_quo = size_x, si_rem = size_y+1;
	uint8_t *ptr_quo = calloc(sizeof(uint8_t), si_quo);
	uint8_t *ptr_rem = calloc(sizeof(uint8_t), si_rem);

	uint8_t **quotient = &ptr_quo, **remainder = &ptr_rem;

	division(quotient, &si_quo, remainder, &si_rem, x, size_x, y, size_y);

	uint8_t quo_len = len(*quotient, si_quo), rem_len = len(*remainder, si_rem);
	
	//輸出商數和餘數
	printf("Quotient: ");
	if (quo_len == 0) printf("0\n");
	else{
		for (int32_t i = quo_len-1; i>=0; i--){

			printf("%hhu", *(*quotient+i));
			if (i==0) puts("");

		}
	}

	printf("Remainder: ");
	if (rem_len ==0) printf("0\n");
	else{
		for (int32_t i = rem_len-1; i>=0; i--){

			printf("%hhu", *(*remainder+i));
			if (i==0) puts("");

		}
	}
	
	return 0;
}

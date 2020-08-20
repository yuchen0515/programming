#include <stdio.h> 		//引入標頭檔<stdio.h> 以便標準輸入輸出
#include <stdint.h>		//引入標頭檔<stdint.h> 作為宣告標準integer型態(type)之用

int main(){		//告訴編譯器 這裡是程式的進入點
	
	/*
		運用<stdint.h>的標準integer型態

		行13: 宣告型別為int32_t 的 變數 digit (存放使用者輸入的 5-digits integer)
		行14: 宣告型別為int32_t 的 變數 temp (暫存為digit的值，以便數值變化仍可有原始值(digit))
		行15: 宣告型別為int32_t 的 變數 result (存放結果的數值)
	 */
	int32_t digit = 0;
	int32_t temp = 0;
	int32_t result = 0;

	//行18-19: 提示使用者輸入一長度五位數的整數 並將數值讀入變數 digit
	printf("Please enter a 5-digits integer: ");
	scanf("%d",&digit);

	//行22: temp存放digit的數值，將用來計算result
	temp = digit;


	/*
		迴圈想法：
		1. 利用temp存放digit
		2. 每跑一次迴圈會將temp除以10，並無條件捨去小數點
		3. 每次都取temp的個位數，加至result變數內
		4. 因為temp每次都會少一位數，跑完五次數值為0，跳出迴圈

	   */
	while (temp){ 						//當temp > 0 時，跑迴圈，否則跳出

		result = result + temp % 10;	//result的數值為 temp的個位數
		temp = temp / 10;				//temp的數值除以10，又因temp為int型態，故無條件捨去

	}

	printf("Result: %d\n", result);		//輸出結果值

	return 0;							//告訴編譯器main()函式可以結束了

}

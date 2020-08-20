//問題：printf函式有回傳值嗎？這值是什麼型態？這值代表什麼意思？
//		請寫一個簡單的程式展示這如何運作的

//回答：是的！printf有回傳值，這個數值是整數型態，
//		代表你所傳送的字符串長度
//		例如今天你輸出"Hello World!\n"
//		Hello加空格以及World!，長度共12，而\n被視作1個長度
//		因此會輸出13
//
//		測試二：假使今天printf內要輸出變數值呢？
//		如下方程式碼，起初設p=0，並printf("Hello World!%d\n")
//		因為最終輸出的狀況為 "Hello World!0\n"，因此會輸出14
//		
//		假使p=10，做一樣的實驗，因為最終輸出是"Hello World!10\n"，
//		長度為15，因此會回傳15
//		p=100也是一樣的道理=>回傳16



//這是簡易的測試printf的回傳值 小程式

#include <stdio.h> 	//引入標頭檔<stdio.h>，即標準I/O輸出輸入
#include <stdint.h>

int main(){		//告知一個程式的進入點

	int32_t p = 0;

	//回傳值為 printf("Hello World!") 將其回傳值代入到%d內
	printf("\"Hello World!\\n\" the value of printf return: %d\n\n",printf("Hello World!\n"));

	printf("The value of p is %d\n",p);
	printf("\"Hello World!%%d\\n\" the value of printf return: %d\n\n",printf("Hello World!%d\n",p));

	p = 10;
	printf("The value of p is %d\n",p);
	printf("\"Hello World!%%d\\n\" the value of printf return: %d\n\n",printf("Hello World!%d\n",p));

	p = 100;
	printf("The value of p is %d\n",p);
	printf("\"Hello World!%%d\\n\" the value of printf return: %d\n",printf("Hello World!%d\n",p));

	return 0; //回傳數值後 即將主程式跳出
}

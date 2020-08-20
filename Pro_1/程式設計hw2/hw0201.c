#include <stdio.h>	//引入<stdio.h>標準輸入輸出的標頭檔
#include <stdint.h>	//引入<stdint.h>標準整數型態的標頭檔

int main(){			//提示函數的進入點

	int32_t a = 0, b = 0, c = 0;	//使用者輸入的三個邊
	int32_t temp_a=0, temp_b=0;	//作為比較大小的暫存變數

	//提示使用者輸入三個整數的邊
	printf("Please enter three edge lengths (integer) of a triangle: ");	
	//讀入三個邊的數值到a,b,c變數內
	scanf("%d %d %d", &a, &b, &c);
	
	//檢查輸入是否存在負數或為零，若是則提示使用者重新輸入
	while (a<=0 || b<=0 || c<=0){
		printf("input error!\n");
		printf("The edge lengths cannot allow negative integer or zero\n");
		printf("Please enter three edge lengths (integer) again: ");
		scanf("%d %d %d", &a, &b, &c);
	}

	/*
	   以下將利用temp_a temp_b
	將兩兩比較較高的數值給予temp_a，另一個數值則存入temp_b
	最後再更新a,b,c的數值
	*/
	
	//a,b做比較，並將較大的數值存進a
	temp_a = a > b ? a:b;
	temp_b = a <= b ? a:b;
	a = temp_a; b= temp_b;

	//b,c做比較，並將較大的數值存進b
	temp_a = b > c ? b:c;
	temp_b = b <= c ? b:c;
	b = temp_a; c= temp_b;

	//此時b的數值有可能比a還大(即起初a,b,c數值，c最大就會發生這種情況)
	//再次a,b做比較，並將較大的數值存入a
	temp_a = a > b ? a:b;
	temp_b = a <= b ? a:b;
	a = temp_a; b= temp_b;
	
	//此時，a,b,c的數值，為遞減序列，即a最大，c最小

	/*
 	 因銳角、直角、鈍角的比較是利用各邊長之平方關係
	 故設置a,b,c三個平方的變數以簡化比較過程
	*/
	int32_t square_a = a*a, square_b= b*b, square_c = c*c;
		
	//因a,b,c已做好排序，當「兩邊和小於第三邊」不成立時，便無法形成三角形
	if (!(b+c >a)){	
		printf("These three numbers don't form to triangle\n");
	}else if (square_a < square_b + square_c){	//兩邊平方和小於最大邊平方和為銳角三角形
		printf("1\n");
	}else if (square_a == square_b + square_c){	//兩邊平方和等於最大邊平方和為直角三角形
		printf("2\n");
	}else if (square_a > square_b + square_c){	//兩邊平方和大於最大邊平方和為頓角三角形
		printf("3\n");
	}else{	//雖上述情況已涵蓋所有情況，但若有未考慮到的情況將輸出"Unknow"
		printf("Unknow\n");
	}

	return 0;	//回傳數值出去，已結束這個函數(函數1.輸入值 2.做某些事 3.輸出) 
}

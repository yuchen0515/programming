/*
	hw0206--problem 6

	(1) Does the scanf function have the return value? What is the return type?
	Ans: 沒錯，而且回傳的型別為「整數」
	(2) What is the meaning of the return value?
	Ans: 這個數值意味著「"接收"到的"格式化"數量」

	ex: scanf("%d %d",&a , &b); =>傳入兩個變數=>會回傳2
   */

#include <stdio.h>
#include <stdint.h>

int main(){

	int32_t a=0, b=0, c=0, d=0;

	printf("Please enter a integer (a): ");
	printf("value of integer: %d\nthe scanf value of return: %d\n",a, (scanf("%d",&a)));

	printf("------------------------\n");
	printf("Please enter two integer (a b): ");
	printf("value of integer: %d %d\nthe scanf value of return: %d\n",a, b, (scanf("%d %d",&a,&b)));
	printf("------------------------\n");
	printf("Please enter three integer (a b c): ");
	printf("value of integer: %d %d %d\nthe scanf value of return: %d\n",a, b, c, (scanf("%d %d %d",&a,&b,&c)));

	return 0;
}

#include <stdio.h>	//引入標頭檔<stdio.h>以便標準輸入、輸出
#include <stdint.h>	//引入標頭檔<stdint.h>以便使用標準整數型態
#include <stdbool.h>	//引入<stdbool.h>以便使用bool型態
#include <math.h> //引入標頭檔<math.h>以便使用sqrt函式

double pow_(double x, int32_t y){
	if (y==0) return 1;
	if (!(y&1)) return pow_(x,y>>1) * pow_(x,y>>1);
	else if (y&1) return pow_(x,y>>1) * pow_(x,y>>1) * x;
}

int main(){	//提示主函式的進入點

	int32_t num = 0, check = 0;
	size_t i = 0;

	printf("Please enter the point number: ");	//提示使用者輸入點的數量
	scanf("%d", &check);

	while (!(check > 0)){	//檢查使用者輸入的數量必須大於0
		printf("Input error! your number isn't over 1\n");
		printf("Please enter the point number: ");
		scanf("%d", &check);
	}
	num = check;

	int32_t arrx[num], arry[num];	//存x,y座標
	double avex = 0, avey = 0;	//x,y的平均

	//讀取x,y座標，順便計算平均
	for (i = 0; i < num; i++){
		printf("Please enter Point %ld: ", i+1);
		scanf("%d %d", &arrx[i], &arry[i]);
		avex += arrx[i];
		avey += arry[i];
	}

	//平均
	avex = avex / num;
	avey = avey / num;

	//存xy的離均差平方(upper, upper2)
	//存x,y離均差相乘
	double upper = 0, upper2 = 0, upper3 = 0;

	for (i = 0 ; i < num; i++){
		upper += pow_((arrx[i] - avex),2);
		upper2 += pow_((arry[i] - avey),2);
		upper3 += ((arrx[i] - avex) * (arry[i] - avey));
	}

	bool check_lower = false;
	double a = 0 , b = 0;
	double sdx = sqrt(upper/num);	//算x的標準差
	double sdy = sqrt(upper2/num);	//算y的標準差
	double ral_lower = sdx * sdy * num;

	if (ral_lower ==0)	check_lower = true;
	else{
		double ral = upper3 / ral_lower;	//利用x,y標準差，推出相關係數
		if (sdx ==0)	check_lower = true;
		else{
			a = ral * (sdy/sdx);	//依標準差、相關係數推出a的值(迴歸直線的斜率)
			b = avey - ral*(sdy/sdx)*avex;	//依平均、相關係數、標準差推出b(迴歸直線截距)
		}
	}
	if (check_lower){	//因為hw4題目敘述說不需要找垂直的線，所以要不斷檢查分母是否為0
		printf("Regression Equation isn't exist\n");
	}else{		//若有正常的斜率跟截距就印出來
		printf("Regression Equation: y = %.2lf x + %.2lf\n", a, b);	//題目hw4印到小數點後第二位
	}

	return 0;
}

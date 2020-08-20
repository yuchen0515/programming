#include <stdio.h>			//引入標頭檔<stdio.h>，以便標準輸入和輸出
#include <stdint.h>			//引入標頭檔<stdint.h>，以便使用標準整數型態
#include <stdlib.h>			//引入標頭檔<stdlib.h>，以便使用裡面的abs
#include <math.h>			//引入標頭檔<math.h>，以便使用三角函數

#define pi (16*atan(1/5.0)-4*atan(1.0/239))		//利用計算pi最簡潔的式子定義pi

void rotate (double *x, double *y, double theta){		//套用旋轉矩陣

	double entry00 = *x * (cos(-theta));
	double entry10 = *y * (-sin(-theta));
	double entry01 = *x * (sin(-theta));
	double entry11 = *y * (cos(-theta));

	//四捨五入到小數點後第三位
	*x = round((entry00 + entry10)*pow(10,3))/pow(10,3);		
	*y = round((entry01 + entry11)*pow(10,3))/pow(10,3);

	//解決-0.000的情況
	if (*x ==0) *x = abs(*x);
	if (*y ==0) *y = abs(*y);
}

int main(){			//提示主函數的進入點

	double x = 0.0 , y = 0.0, theta = 0;
	double *ptr_x = &x, *ptr_y = &y;

	//提示輸入
	printf("Please enter a point: ");
	scanf("%lf %lf", ptr_x, ptr_y);
	printf("Please enter theta (0-360): ");
	scanf("%lf", &theta);

	//檢查使用者輸入的角度
	while (!(theta>=0 && theta<=360)){
		printf("Input error! your values isn't on [0,360]\n");
		printf("Please enter theta (0-360): ");
		scanf("%lf", &theta);
	}

	//將theta轉弧度，丟進rotate函數
	rotate(ptr_x, ptr_y, ((pi/180)*theta));

	//印到小數點後第三位
	printf("%.3lf %.3lf\n", *ptr_x, *ptr_y);

	return 0; 
}

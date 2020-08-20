#include <stdio.h>	//引入標頭檔<stdio.h>, 以便標準輸入輸出

int main(){			//告知主函式的進入點 由此處開始跑
	
	/* 行10-13
		設置使用者輸入之第一、二筆座標為變數
		第三筆座標的x軸和y軸初始化;
		slope為該方程式之斜率
	   */
	float x1 = 0.0, y1 = 0.0;
	float x2 = 0.0, y2 = 0.0;
	float x = 0.0, y = 0.0;
	float slope = 0.0;
	
	//行16-19 使用者提示介面--告知程式用途
	printf("The program will calculate the linear equation by the two points\n");
	printf("When you enter the value of x, showing its y value\n");

	printf("---------------------------------------------------\n");
	//行21-25 使用者提示介面--提示輸入座標
	printf("Please enter the 1st point (x1 y1): ");
	scanf("%f %f", &x1, &y1);

	printf("Please enter the 2nd point (x2 y2): ");
	scanf("%f %f", &x2, &y2);

	//行28-34 避免使用者輸入相同座標，直到輸入不同座標時才會跳出迴圈
	while (x1 == x2 && y1 == y2){

		printf("輸入錯誤！您輸入的兩點是相同的座標\n");
		printf("請再輸入一組座標(x2 y2): ");
		scanf("%f %f", &x2, &y2);

	}
	
	//行37-38 提示輸入第三組座標的x-value
	printf("Please enter x of the 3rd point: ");
	scanf("%f", &x);

	/* 行46-59
		檢查x1是否等於x2，若等於則方程式為鉛垂線
		此時要再檢查第三筆座標的x值是否相等
		如果相等的話，雖在該直線上，但y值並不唯一
		反之，則不在方程式上，無法輸出y值
	   */
	if (x1 == x2){
		
		printf("the eqution is \"x = %.1f\"\n",x1);

		if (x1 == x){

			printf("此直線方程式為鉛錘線，任何y值皆可能成立\n");

		}else{

			printf("您輸入的x值不在方程式上\n");

		}
	}else{
	/*
		若x1不等於x2，此時可算出斜率
		再利用 y = mx + -x1m1+y1 計算出直線方程式
		使用該方程式即可算出第三組座標的y值
	   */
		slope = ( y1 - y2 ) / ( x1 - x2 );
		printf("該直線方程式為 y = (%.1f) x + (%.1f)\n", slope, slope * ( -x1 ) + y1 );
		y = slope * ( x - x1 ) + y1;
		printf("您輸入的x值為 %.1f, 其對應的y值為 %.1f\n", x, y);

	}

	return 0;
}

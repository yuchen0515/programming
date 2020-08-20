#include <stdio.h>	//引入標頭檔<stdio.h>，以便標準輸入和輸出
#include <stdint.h>	//引入標頭檔<stdint.h>，以便使用標準整數型態
#include "hw0401_header.h"	//引入自製的標頭檔<hw0401_header.h>，以便使用hanoi_re
#define limit 20

//建立二維陣列存取三條桿子的狀態
int32_t rod[3][limit]= {0};

int main(){ //提示主函數進入點 
	
	//disk表示盤子大小，check則負責檢查使用者輸入的數字是否在[2,20]內
	int32_t disk = 0, check = 0;

	//提示使用者輸入盤子的數量
	printf("Please enter the disk number (2-20): ");
	scanf("%d", &check);

	//檢查使用者輸入的數量是否在[2,20]內，若否則提示重新輸入
	while (!(check >=2 && check <=20)){
		printf("Input error! your valus isn't on the interval [2,20]\n");
		printf("Please enter the disk number (2-20): ");
		scanf("%d", &check);
	}

	disk = check;

	//由後往前存盤子，以便模擬"堆疊"型態
	for (int32_t i = disk; i>0 ; i--){
		rod[0][i-1] = disk-i+1;
	}

	//跑一次標頭檔內的迴圈版hanoi塔
    hanoi_for(disk, rod);

	return 0;	//回傳0以跳出主函數
}

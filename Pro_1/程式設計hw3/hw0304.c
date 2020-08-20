#include <stdio.h>		//引入標頭檔<stdio.h>以便標準輸入和輸出
#include <stdint.h>		//引入標頭檔<stdint.h>以使用標準整數型態
#include <math.h>		//引入標頭檔<math.h>以便使用sqrt, pow等函式

int main(){			//提示主函數的進入點

	int32_t n=0;	//用以儲存使用者所輸入的n值
	//提示使用者輸入數字n (介於1-50000000之間)
	printf("Please enter n (1-50000000): ");
	scanf("%d",&n);

	//檢查使用者輸入的範圍，若在範圍外則提示重新輸入
	while (!(n>=1 && n<=50000000)){
		printf("input error! your values isn't in the interval [1,50000000]\n");	
		printf("Please enter n (1-50000000): ");
		scanf("%d",&n);
	}

	//題目是指"that are smaller than n" 因此計算到n-1 (外圈)
	for (int32_t i=1; i<n; i++){
		//宣告計算因數總和的變數
		int32_t sum_divisor = 0;

		//內圈一直計算到sqrt(i)，以便優化速度
		for (int32_t j=1; j<(int)sqrt(i)+1;j++){

			//當可以整除，且數值不等於自己，則將該因數加進sum_divisor內
			if (i%j==0 && i!=j){
				sum_divisor+= j;
				//此外若 j*(i/j) = i，當j不等於(i/j)時即加上(i/j)的值
				if (j != (i/j) && j!=1)	sum_divisor+= (i/j);
			}
			
			//若sum_divisor早就超過我們要求的數字，直接跳出迴圈
			if (sum_divisor > i)	break;
		}

		//若因數(不包含自己)相加後等於自己，就輸出
		if (i==sum_divisor){
			printf("%d\n",i);
		}
	}

	return 0;	//回傳值結束主函數
}

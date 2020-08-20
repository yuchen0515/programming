#include <stdio.h>		//引入標頭檔<stdio.h> 以便標準輸入輸出
#include <stdint.h>		//引入標頭檔<stdint.h>以便使用標準整數型態

int main(){				//提示主函數的進入點

	int32_t k = 0;		//設置k變數儲存使用者輸入
	double taylor = 1.0, temp = 1.0;	//double版本的最終結果，設為1.0是為了方便第0項的計算
	float ftaylor = 1.0, ftemp = 1.0;	//float的版本

	//提示使用者輸入
	printf("k-th order Taylor polynomial for e\n");	
	printf("Please enter a non-positive integer k: ");
	scanf("%d",&k);

	//檢查使用者輸入k值是否為非負
	while (k<0){
		printf("inpur error! k isn't negative.\n");
		printf("Please enter a non-positive integer k again: ");
		scanf("%d",&k);
	}

	//要計算的是e^1次方，因此x部份代入1，透過迴圈計算階乘
	for (int32_t i=1; i<=k; i++){

		//分子刻意使用"1.0"，透過float強制將i跟著cast成float
		temp = temp* (1.0/i);	
		ftemp = ftemp* (1.0/i);

		taylor = taylor + temp;
		ftaylor = ftaylor + ftemp;

	}

	//輸出結果
	printf("k-th order Taylor polynomial for e of double number: %.20lf\n", taylor);
	printf("k-th order Taylor polynomial for e of float number: %.20lf\n", ftaylor);

	return 0;
}

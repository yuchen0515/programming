#include <stdio.h>		//引入標頭檔<stdio.h>以便標準輸入和輸出
#include <stdint.h>		//引入標頭檔<stdint.h>以便使用標準整數型態

int main(){				//提示主函數的進入點

	double fund = 0;	//用以儲存使用者輸入的"每月固定存入"的基金額度
	double rate = 0.0;	//用以儲存使用者輸入的"年利率"

	//提示使用者輸入在[1000,50000]區間內的每月投資金額 
	printf("Please enter your monthly investment amount (1000-50000): ");
	scanf("%lf",&fund);
	//檢查使用者的輸入是否超出[1000,50000]
	while (!(fund>=1000 && fund<=50000)){
		printf("input error! your values isn't in the interval [1000,50000]\n");
		printf("Please enter your monthly investment amount (1000-50000): ");
		scanf("%lf",&fund);
	}

	//提示使用者輸入年利率
	printf("Please enter your anticipated annual rate (%%): ");
	scanf("%lf",&rate);

	//月利率=年利率/12，但是因為輸入的為百分比，因此講數值再除以100方便計算
	double mon_rate_aver = (rate/1200);
	double mon_rate_max = ((rate+3)/1200);
	double mon_rate_min = ((rate-3)/1200);

	//以下aver, max, min皆儲存"複利和" 只是以不同的年利率去計算

	//用以計算(average)
	double aver = 0.0;
	//計算最大、最小值，在下方最先將最大、最小值設為第一個數字，以方便計算
	double max = 0.0, min = 0.0;

	//外圈跑20年的迴圈，內圈跑12次月複利
	for (int32_t i=0;i<20;i++){

		for (int32_t j=0;j<12;j++){

			aver = aver + fund;			//以輸入的年利率計算複利和
			aver = aver * ( 1 + mon_rate_aver );

			max = max + fund;			//以(輸入的年利率+3%)計算複利和
			max = max * ( 1 + mon_rate_max );

			min = min + fund;			//以(輸入的年利率-3%)計算複利和
			min = min * ( 1 + mon_rate_min );

		}


		printf("Year %d: %lf (max) %lf (average) %lf (min)\n",i+1, max, aver, min);
	}

	return 0;	//回傳數值後以便跳出主函數
}


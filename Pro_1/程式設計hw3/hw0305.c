#include <stdio.h>			//引入<stdio.h>標頭檔，以便標準輸入輸出
#include <stdint.h>			//引入<stdint.h>標頭檔，以使用標準整數型態

int main(){		//提示主函數進入點

	int32_t num = 0;	//儲存使用者輸入的值	
	//提示使用者輸入
	printf("Please enter a non-negative number: ");
	scanf("%d",&num);

	//檢查使用者輸入是否為非負，若為負數則提示使用者重新輸入
	while (!(num>=0)){
		printf("input error! your values isn't a non-negative number or over int range\n");
		printf("Please enter a non-negative number: ");
		scanf("%d",&num);
	}

	//利用temp暫存
	int32_t temp = num;

	//直到temp剩下一位數時，才會跳出迴圈	
	while (temp>=10){
		int32_t sum = 0;	//利用sum計算總和

		while (temp>0){		//內迴圈再跑每一次的digit疊加
			//分成temp>=10和temp>0兩邊，即可判斷+和=位置應如何擺放
			if (temp>=10){

				printf("%d + ", temp%10);
				sum = sum + (temp%10);
				temp = temp/10;

			}else if (temp>0){

				sum = sum + temp;
				printf("%d = %d\n", temp, sum);
				temp = 0;

			}
		}
		//將加總後的結果再做一次一樣的動作，直到總和為1位數為止
		temp= sum;
	}

	//輸出最終結果
	printf("Final: %d", temp);

	return 0;

}

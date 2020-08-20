#include <stdio.h>		//引入標頭檔<stdio.h>，以便標準輸入和輸出
#include <stdint.h>		//引入標頭檔<stding.h>，以使用標準整數型態

int main(){				//提示主函數的進入點

	int32_t h = 0;		//儲存使用者輸入的高度
	int32_t p[10] = {0};	//作為儲存帕斯卡三角形單行的陣列

	//提示使用者輸入高度h，若超出區間則提示使用者重新輸入
	printf("Please enter the height of a Pascal's Triangle (1-10): ");
	scanf("%d",&h);
	while (!(h>0 && h<=10)){
		printf("input error! You enter value should be the interval[1,10]\n");
		printf("Please enter the height of a Pascal's Triangle (1-10) again: ");
		scanf("%d",&h);
	}

	//區間位於[1,10]，則第一行必定會輸出一個1，為防止p[j-1]超出邊界的問題，故事前輸出
	p[0] = 1;
	printf("%d\n",p[0]);

	//外迴圈負責跑第1~h行，內迴圈則由右往左替代數字，並輸出(以\t分隔)
	for (int32_t i=1; i<h; i++){
		for (int32_t j=h-1;j>=1;j--){
			if(j==h-1){					//將原本該列最後一個1，往後移一格
				p[h-1] = p[h-2];
			}else{						//將原本該列的數值，轉為該格加上前一格數字取代之
				p[j] = p[j]+p[j-1];
			}
		}

		//負責輸出數值
		for (int32_t j=0; j<=i; j++){
			printf("%d\t",p[j]);
		}

		//單行輸出結束，換行
		printf("\n");
	}

	return 0;		//回傳0跳出主函數
}

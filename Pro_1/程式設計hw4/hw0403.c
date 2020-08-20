#include <stdio.h>	//引入標頭檔<stdio.h>，以便標準輸入和輸出
#include <stdint.h>	//引入標頭檔<stdint.h>，以便使用標準整數型態
#include <stdbool.h>	//引入標頭檔<stdbool.h>，以使用布林型態

int main(){		//提示主函數進入點

	//以index(指引目前位置)和buffer(儲存十個動作)
	int32_t index = 0, check = -1, buffer[10];
	size_t i = 0;

	//初始化
	for (i=0; i<10; i++) buffer[i] = -3;

	//跑迴圈，直到使用者輸入0為止
	while (true){

		//提示輸入數值(動作)
		printf("Please enter your action: ");
		scanf("%d", &check);

		//檢查數值是否大於等於-2
		while (!(check>=-2)){
			printf("Input error! your number both isn't a action and positive number!\n");
			printf("Please enter your action: ");
			scanf("%d", &check);
		}

		//等於0就跳出
		if (check ==0){
			index--;
			break;
		}

		//索引值等於10[buffer爆出]且採取動作不為復原、取消復原，則將最舊的數字汰換掉
		if (index==10 && check!=-1 && check!=-2){
			for(int32_t p=0; p<9; p++){
				buffer[p] = buffer[p+1];	
			}
			//重新定位索引值為9，並將數值存進
			index = 9;
		}

		//復原的前提在於buffer必須要有數值，因此亦檢查index必須大於0	
		if (index > 0 && check ==-1){
			index--;
		//取消復原的前提在於前個動作要復原過，因此檢查下一數值是否不等於初始值
		}else if (check == -2 && buffer[index+1]!=-3){
			index++;	
		//除上述行為以外的數值，將數值存入buffer[index]
		}else if (check >= 1){
			buffer[index] = check;
			index++;
		}

	}

	//從0跑到不為初始值的數並且需要小於10
	for (i=0 ; buffer[i]!=-3 && i<10 ; i++){

		printf("%d", buffer[i]);
		//等於index則指出位置在這
		if (i == index)	printf("(*) ");
		else printf(" ");

	}
	//println
	printf("\n");

	return 0;
}

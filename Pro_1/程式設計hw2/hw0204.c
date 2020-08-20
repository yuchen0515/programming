#include <stdio.h>		//引入標頭檔<stdio.h>以便標準輸入和輸出
#include <stdint.h>		//引入標頭檔<stdint.h>以使用標準整數型態

int main(){		//提示主函數的進入點

	int32_t card[3] = {0, 0, 0};	//宣告大小為三個陣列，預設值為0
	int32_t point = 0;	//宣告之後點數的數值變數為point
	int32_t not_in_bound = 0;
	//提示使用者輸入介於1~52的三張牌
	printf("Please enter numbers of three cards on the interval [1,52]: ");
	//將使用者輸入分別讀入card陣列內
	
	//檢查使用者輸入的卡牌是否在1~52之間，若不是則在下面的迴圈中提示重新輸入
	for (int32_t i=0; i<3;i++){
		scanf("%d",&card[i]);
		if (!(card[i]<=52 && card[i]>0)){
			not_in_bound = 1;
		}
	}

	//檢查使用者是否輸入了相同的牌(一副牌只有52張，每張牌是唯一)
	//重複的話，再次提示使用者重新輸入
	while ((not_in_bound==1)||(card[0] == card[1]) || (card[0] == card[2]) || (card[1] == card[2])){
		not_in_bound = 0;
		printf("Each card cannot be the same or not in bound!\n");
		printf("Please enter numbers of three cards on the interval [1,52]: ");
		scanf("%d %d %d",&card[0], &card[1], &card[2]);
		if (!(card[0]<=52 && card[0]>0)){
			not_in_bound = 1;
		}
		if (!(card[1]<=52 && card[1]>0)){
			not_in_bound = 1;
		}
		if (!(card[2]<=52 && card[2]>0)){
			not_in_bound = 1;
		}
	}

	//依序讀取三張牌，並按照判斷累加點數
	//累加完將變數初始化為0，如遇1則保留數值，以便之後的判斷
	for(int i=0; i<3; i++){
		switch (card[i]%13){	//以卡牌 mod 13的數值去switch
			case 0:
			case 11:
			case 12:	//若牌面mod 13是0、11或12(即J,Q,K)則...
				point = point + 10;	//face card一律為10點
				card[i] = 0;
				break;
			case 1:		//若為ACE，先將數值加1，並將卡牌值保留
				point = point + 1;
				break;
			default:	//若為其他牌，則加上該牌點數的數值
				point = point + card[i]%13;
				card[i] = 0;
		}
	}

	for (int i=0;i<3;i++){	//除了Ace以外的牌都以設為0，接著要一一讀取
		//若卡牌不為0(必為Ace)，且點數+10不會超出21，則將點數+10(原本就已經加1了)
		if (card[i] && (point+10) <=21){	
			point = point+10;
		}
	}

	//超出21則輸出bust
	if (point > 21){
		printf("bust\n");
	}else if (point <= 21){	//沒超出21則輸出點數
		printf("%d\n",point);
	}else{	//其他情況則輸出錯誤
		printf("output error\n");
	}
	
	return 0;
}

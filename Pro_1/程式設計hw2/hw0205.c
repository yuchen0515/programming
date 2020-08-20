#include <stdio.h>	//引入標頭檔<stdio.h>，以便標準輸入和輸出
#include <stdint.h>	//引入標頭檔<stdint.h>，以便使用標準整數型別

int main(){		//提示主函數的進入點
	
	//設置二元狀態判斷 straight(順)、flush(同花)
	int32_t straight = 0, flush = 0, pair = 0;
	//二元狀態判斷 four_of_a_kind(四條)、three_of_a_kind(三條)
	int32_t four_of_a_kind = 0, three_of_a_kind = 0;
	//二元狀態判斷 輸入卡牌點數重複(repeat)、separate(散牌數)、not_in_bount(超出1-52範圍)
	int32_t repeat = 0, separate = 0, not_in_bound = 0;
	int32_t suit[4] = {0};	//花色陣列，0,1,2,3依序紀錄每個花色出現次數
	int32_t card[5] = {0};	//手牌陣列，依序讀入使用者輸入的五張牌

	//卡牌點數陣列，儲存每個點數出現幾次
	//特別的是，point[13]是儲存ACE出現的次數，和point[0]一樣，為了方便順子的判斷
	int32_t point[14] = {0};	

	//提示使用者輸入五張牌，並介於1-52之間
	printf("Please enter 5 cards on the interval [1,52]: ");
	for(int32_t i=0; i<5; i++){	//讀入五張牌
		scanf("%d",&card[i]);
		//每張牌判斷是否在範圍內，若不是則記錄下來
		if (!(card[i]<=52 && card[i]>0))	not_in_bound = 1;
	}

	//兩兩判斷卡牌是否相同(每張牌唯一)，若相同則記錄下來
	for (int32_t i=0; i<4; i++)
		for (int32_t j=i+1; j<5;j++){
			if (card[i] == card[j]){
				repeat = 1;
				//break只會跳脫一層，因此直接將i設為4，以便跳出最外迴圈
				i = 4;
				break;
			}
		}

	//若輸入重複，或超出邊界，則提示使用者重新輸入卡牌
	while (repeat ==1 || not_in_bound == 1){
		printf("input error! The cards cannot be the same, or not in bound!\n");
		printf("Please enter 5 cards on the interval [1,52] again: ");
		//先將repeat, not_in_bound設為0，之後再持續進行判斷，否則會陷入無限迴圈
		repeat = 0;
		not_in_bound = 0;

		//讀入資料，並確認是否在範圍內
		for(int32_t i=0; i<5; i++){
			scanf("%d",&card[i]);
			if (!(card[i]<=52 && card[i]>0))	not_in_bound = 1;
		}

		//兩兩比較，確認是否重複
		for (int32_t i=0; i<4; i++)
			for (int32_t j=i+1; j<5;j++){
				if (card[i] == card[j]){
					repeat = 1;
					i = 4;
					break;
				}
			}
	}

	//五張手牌依序讀取，並在指定的花色或點數上記錄數量
	for (int32_t i = 0; i<5; i++){
		suit[(card[i]-1)/13]++;
		point[(card[i]-1)%13]++;
		//特別的是，當牌=ACE，則除了point[0]紀錄以外，也在point[13]紀錄，以便順子的判斷
		if ((card[i]-1)%13==0)	point[13]++;
	}
	//一一檢查梅花、方塊、紅心、黑桃是否有五張，若是則flush(同花色)紀錄為1
	for (int32_t i=0; i<4;i++){
		if (suit[i]==5){
			flush =1;
			break;
		}
	}

	//一一檢查點數，判斷牌型
	for (int32_t i=0; i<13;i++){
		//若該牌有四張，則"四條"的變數紀錄為1
		if (point[i]==4) four_of_a_kind=1;
		//若該牌有三張，則"三條"的變數紀錄為1
		else if (point[i]==3) three_of_a_kind=1;
		//若該牌有兩張，紀錄"對子"的變數加1(有可能有兩對)
		else if (point[i]==2) pair++;
		//若以上皆否，卻有一張牌，則"散牌"的變數加1(未必是真的散牌)
		else if (point[i]==1) separate++;
	}

	//非對子、三條、四條的牌達到五張則進入該判斷
	if (separate==5){
		//依序走訪0~12 (判斷式檢查到13)
		for (int32_t i =0; i<13;i++){
			//判斷相連點數若恰有一張牌，將"散牌"變數扣1
			if (point[i]==1 && point[i+1]==1){
				separate--;
			}
		}
		//因以這樣的方式判斷，如遇順子，則只會扣四次
		//例如1,2,3,4,5，相鄰時扣除=>1,2／2,3／3,4／4,5
		//因此separate會變為1，但倘若只有四張相連，則扣三次，三張相連，扣兩次，依此類推
		
		//若有K,1,2，則separate要加回去(因為在判斷point[12],point[13]時有多扣一次)
		if ((point[0]==1 && point[1]==1) && point[12]==1) separate++;

		//因此判斷separate為1，則確定為順子(此外10,J,Q,K,A亦為順子，故利用point[13]判斷
		if (separate == 1)	straight = 1;
		else	straight = 0;


	}

	//既是同花色，又是順子=>同花順
	if (flush==1 && straight ==1)	printf("Straight flush\n");
	//非同花順，但有四條=>鐵支
	else if (four_of_a_kind==1)	printf("Four of a kind\n");
	//非上述情況，卻有三條+一對=>葫蘆
	else if (three_of_a_kind==1 && pair==1)	printf("Full house\n");
	//非上述情況，卻為同花色=>同花
	else if (flush==1)	printf("Flush\n");
	//非上述情況，卻為順子=>順子
	else if (straight==1)	printf("Straight\n");
	//非上述情況，卻有三條=>三條(葫蘆的情況已經排除)
	else if (three_of_a_kind==1)	printf("Three of a kind\n");
	//非上述情況，卻有兩個對子=>two pairs
	else if (pair ==2)	printf("Two pair\n");
	//非上述情況，有一對=> pair
	else if (pair ==1)	printf("One pair\n");
	//上述情況皆非，散牌
	else 	printf("High card\n");

	return 0;	//回傳0，跳出主函數
}

#include <stdio.h>
#include <stdint.h>
#include "hw0601.h"

//助教的shuffle
void shuffle(uint8_t *player1, uint8_t *player2, uint8_t *player3, uint8_t *player4) {
    uint8_t card[52] = {45, 26, 10, 43, 19, 51, 50, 16, 36, 31, 20, 38, 41, 37, 34, 7, 13, 12, 27, 5, 48, 46, 42, 1, 6, 21, 17, 28, 8, 15, 2, 33, 4, 3, 22, 29, 9, 11, 49, 40, 30, 35, 24, 39, 44, 23, 52, 14, 47, 32, 18, 25};
    for(int i = 0; i < 13; i++) {
        player1[i] = card[i];
    }
    for(int i = 0; i < 13; i++) {
        player2[i] = card[i + 13];
    }
    for(int i = 0; i < 13; i++) {
        player3[i] = card[i + 26];
    }
    for(int i = 0; i < 13; i++) {
        player4[i] = card[i + 39];
    }
}

//列印牌的函數
void print_card(const uint8_t player[13]){
	for (int32_t i = 0 ;  i<13; i++){
		printf("%d ",player[i]);
	}
	puts("");
}

//檢查手牌有沒有問題
int32_t check_card(uint8_t a[13], uint8_t b[13], uint8_t c[13], uint8_t d[13]){
	int32_t temp[52] = {0};
	for (int32_t i = 0 ; i < 13; i++){
		//超出範圍
		if (((a[i]>52 || a[i]<=0)) || ((b[i]>52 || b[i]<=0)) || ((c[i]>52 || c[i]<=0)) || ((d[i]>52 || d[i]<=0))) return 1;
		//一張牌出現多次
		if (((++temp[a[i]-1]) > 1)||((++temp[b[i]-1]) > 1)||((++temp[c[i]-1]) > 1)||((++temp[d[i]-1]) > 1)) return 1;
	}
	return 0;
}

//compare function 1
int32_t func01(int32_t a, int32_t b){
	//位移後取餘數，K即可成為取餘數後最大的值，沒有調整的話這樣K會被最小的
	if ((a+12)%13 > (b+12)%13) return 1;
	return 0;
}

//compare function 2
int32_t func02(int32_t a, int32_t b){
	//一樣位移，讓2取餘數變成最大
	if ((a+10)%13 > (b+10)%13) return 1;
	return 0;
}

//compare function 3
int32_t func03(int32_t a, int32_t b){
	//先按點數排
	if ((a+12)%13 > (b+12)%13) return 1;
	//如果點數一樣再按花色排(一般玩大老二會這樣排)
	if (((a+12)%13 == (b+12)%13) && (((a-1)/13) > ((b-1)/13))) return 1;
	return 0;
}


//其實直接按輸入值由小到大排序即可
//compare function 4
int32_t func04(int32_t a, int32_t b){
	//先按花色排
	if ((a-1)/13 > (b-1)/13) return 1;
	//如果花色一樣，再按照點數排(此類排序通常在玩橋牌會使用)
	if (((a-1)/13 == (b-1)/13) && ((a+12)%13 > (b+12)%13)) return 1;
	return 0;
}

//排序，引入pointer function
void sort_card(uint8_t player[13], int32_t (*compare)(int32_t a, int32_t b)){
	//氣泡排序法
	for (int32_t i = 0 ; i<12 ; i++){	//最後一個不用排，到那邊時也只剩一個，當然已經排好了
		for (int32_t j = 1 ; j<13-i;j++){
			if (compare(player[j-1], player[j])){
				//利用XOR，可以不宣告變數就能完成交換
				player[j] ^= player[j-1];
				player[j-1] ^= player[j];
				player[j] ^= player[j-1];
			}
		}
	}
}


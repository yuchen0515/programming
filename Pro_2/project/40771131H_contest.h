#pragma once
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//基本款，project.pdf需要的函式
void CSIE_40771131H_setup(int32_t id);
void CSIE_40771131H_deal(const int32_t cards[10]);
int32_t CSIE_40771131H_pick(const int32_t table[4][5], const int32_t score[2], const int32_t last[8], const int32_t card[10]);
int32_t CSIE_40771131H_choose(const int32_t table[4][5], int32_t card);

//自己的其它函式
int32_t CSIE_40771131H_transform(int32_t card);
void CSIE_40771131H_determine_last_index_index(const int32_t table[4][5], int32_t last_index[4], int32_t score[4]);

int32_t CSIE_40771131H_cards[10] = {0};
int32_t CSIE_40771131H_id = 0;
int32_t CSIE_40771131H_choose_max  = 0; 


int32_t CSIE_40771131H_compare(const void *a, const void *b);

typedef struct _CSIE_40771131H_last_status{
	int32_t last;
	int32_t row;
}CSIE_40771131H_last_status;



//static
//Initialization
//id is 0 or 1
void CSIE_40771131H_setup(int32_t id){
	extern int32_t CSIE_40771131H_id;
	CSIE_40771131H_id = id;
}


//Deal 10 cards to you.
void CSIE_40771131H_deal(const int32_t cards[10]){
	extern int32_t CSIE_40771131H_cards[10];
	for (int32_t i = 0 ; i < 10 ; i++)
		CSIE_40771131H_cards[i] = cards[i];
}

//Return the selected card number.
//Table is used to show the current status.
//Score array is the current score status.
//Last array is used to inform the last run cards.
//If the return value is not a valid card, you will lose.
int32_t CSIE_40771131H_pick(const int32_t table[4][5], const int32_t score[2], const int32_t last[8], const int32_t card[10]){
	typedef struct __last_status{
		int32_t last;
		int32_t row;
	}_last_status;
	//取得deal過的資訊
	static int32_t cards[10] = {0}, check = 0;
	if (check ==0){
		extern int32_t CSIE_40771131H_cards[10];
		for (int32_t i = 0;  i < 10;i++)
			cards[i] = CSIE_40771131H_cards[i];
		check = 1;
	}


	int32_t points[4] = {0}, table_last[4] = {0};
	CSIE_40771131H_determine_last_index_index(table, table_last, points);

	_last_status status[4];

	for (int32_t i = 0 ; i < 4; i ++)
		status[i] = (_last_status){ table[i][table_last[i]] , i };

	qsort(status, 4, sizeof(CSIE_40771131H_last_status), CSIE_40771131H_compare);

	int32_t res = -1 , ans = -1, okk = 0;

	for (int32_t j = 0 ; j < 10 ; j++){
		res = -1;
		if (card[j] != 0 && card[j] != -1){
			okk = j;
			for (int32_t i = 0 ; i < 4; i ++)
				if (status[i].last < card[j]) res = status[i].row;
		}
		if (res != -1 && table_last[res] < 4)
			ans = j;
	}
	if (ans == -1) ans = okk;

	cards[ans] = 0;

	return card[ans];
}


int32_t CSIE_40771131H_transform(int32_t card){
	//根據規則決定牛頭數
	//card, range is fail
	//accepted 0, and -1 => point is 0
	//other range is "error number"
	if (card == 0 || card == -1) return 0;
	else if (card < 0 || card > 104) return -1;

	switch (card){
		//2
		case 5: case 15: case 25: case 35: case 45: case 65: case 75: case 85: case 95: 
			return 2;
			//3
		case 10: case 20: case 30: case 40: case 50: case 60: case 70: case 80: case 90: case 100: 
			return 3;
			//5
		case 11: case 22: case 33: case 44: case 66: case 77: case 88: case 99:
			return 5;
			//7
		case 55:
			return 7;
			//1
		default: 
			return 1; 
	}

}

//If the palyed card is lower than all the latest cards present
//on all rows, the function chooses a row and gather the cards
//on that row.
//card: the card your oppenet pick in this run.
//Return value: 0 <---> 3
int32_t CSIE_40771131H_choose(const int32_t table[4][5], int32_t card){
	//選擇要吃掉哪一排
	int32_t score[4] = {0}, table_last[4] = {0};

	CSIE_40771131H_determine_last_index_index(table, table_last, score);

	//選擇最單純的方式, 挑最少牛頭數的row
	int32_t choose = 0;
	extern int32_t CSIE_40771131H_choose_max;
	for (int32_t i = 1 ; i < 4 ; i++){
		if (score[i] < score[choose]) choose = i;
		if (score[i] > score[choose]) CSIE_40771131H_choose_max = i;
	}

	return choose;
}





void CSIE_40771131H_determine_last_index_index(const int32_t table[4][5], int32_t last_index[4], int32_t score[4]){
	//計算牌面每排最後一個在哪，以及每排牛頭數
	for (int32_t i = 0 ; i < 4 ; i++){
		last_index[i] = 0;
		score[i]= 0;
	}

	for (int32_t i = 0 ; i < 4 ; i++){
		for (int32_t j = 0 ; j < 5 ; j++){
			//單排牌面狀況
			if (table[i][j] == 0) break;
			last_index[i] = j;
			score[i] += CSIE_40771131H_transform(table[i][j]);
		}
	}
}


int32_t CSIE_40771131H_compare(const void *a, const void *b){
	if (((CSIE_40771131H_last_status *) a)->last > ((CSIE_40771131H_last_status *)b)->last) return 1;
	return 0;
}

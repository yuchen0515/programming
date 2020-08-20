#include <stdio.h>			//引入標頭檔<stdio.h>，以便標準輸入和輸出
#include <stdint.h>			//引入標頭檔<stdint.h>，以便使用標準整數型態

//start函數的判斷，純粹改state的數值
void state_start(int32_t *state, int32_t input){
	if ((input==10)||(input==35)) *state=1;
	else if (input==11) *state=3;
	else if ((input==20)||(input==78)) *state=5;
}

void state_s01(int32_t *state, int32_t input){					//S01
	if ((input==12)||(input==36)) *state=6; else if (input==19) *state=2;
}
void state_s02(int32_t *state, int32_t input){					//S02
	if (input==99) *state=7;
	else if (input!=43) *state=0;
}
void state_s03(int32_t *state, int32_t input){ *state = 4; } 	//S03
void state_s04(int32_t *state, int32_t input){ *state = 6; }	//S04
void state_s05(int32_t *state, int32_t input){					//S05
	if (input==1) *state=4;
	else if (input==2) *state=6;
	else *state = 0;
}
void state_s06(int32_t *state, int32_t input){					//S06
	if (input==108) *state=7;
	else *state = 5;
}
void state_final(int32_t *state, int32_t input){}				//final


int32_t main(){			//提示主函數的進入點

	int32_t state = 0, check = 0 ;		//儲存目前狀態，檢查使用者輸入 的變數
	//用二維字元陣列，去放start,s1,...,final，以便最後輸出方便
	char prom[][8] = {"start","s1", "s2", "s3", "s4", "s5", "s6", "final" };
	
	//宣告array of pointer function(8格，依序放每個函數)
	void (*dfa[8]) (int32_t *, int32_t);
	dfa[0] = state_start; 	dfa[1] = state_s01;
	dfa[2] = state_s02; 	dfa[3] = state_s03;
	dfa[4] = state_s04; 	dfa[5] = state_s05;
	dfa[6] = state_s06; 	dfa[7] = state_final;

	while (1){
		printf("Please enter an integer (0-255, -1: stop): ");
		scanf("%d", &check);
		if (check==-1) break;		//-1跳出
		else if (!(check>=0 && check<=255)){		//檢查[0,255]
			printf("Input Error! Your value isn't on [0,255] or -1\n");
			continue;				//重新輸入
		}
		dfa[state](&state, check);	//state 0-7剛好對應dfa[0-7]，可以直接寫成一行
	}
	printf("The user is in the %s state.\n", prom[state]);	//印出最終結果

	return 0;
}

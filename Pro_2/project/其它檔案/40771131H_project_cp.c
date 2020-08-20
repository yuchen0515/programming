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
void __setup_shuffle(int32_t card[], int32_t n);
void range_shuffle(int32_t card[], int32_t n);
void print_player_hand(int32_t player, int32_t **hand_card, int32_t n);
void print_table_status(int32_t table[4][5], int32_t row, int32_t col);
int32_t **declared_two_pointer(int32_t row, int32_t col); 
int32_t look_up_hand_index(int32_t card[10], int32_t val);

int32_t Agent_pick_level_1(int32_t table[4][5], int32_t card[10]);
int32_t Agent_choose_level_1(int32_t table[4][5], int32_t card);
int32_t Agent_pick_level_2(int32_t table[4][5], int32_t card[10]);
int32_t Agent_choose_level_2(int32_t table[4][5], int32_t card);

int32_t pick_one_row(int32_t table[4][5], int32_t score[], int32_t player, int32_t row);

//if return -1, player should choose one row to pick
int32_t put_one_card(int32_t table[4][5], int32_t score[], int32_t player, int32_t card[10], int32_t val);
int32_t put_one_card_and_clear_hand(int32_t card[10], int32_t val);
int32_t put_one_card_in_table_row(int32_t table[4][5], int32_t player, int32_t card[10], int32_t val, int32_t row, int32_t table_last[]);

//print meau
void print_meau_stat_game();
void print_meau_game_setting();
void print_meau_agent_setting();
void print_meau_store();
void print_meau_sort_hand();

typedef struct _last_status{
	int32_t last;
	int32_t row;
}last_status;

int32_t compare(const void *a, const void *b){
	if (((last_status *) a)->last > ((last_status *)b)->last) return 1;
	return 0;
}

int32_t CSIE_40771131H_cards[10] = {0};
int32_t CSIE_40771131H_id = 0;


//可以紀錄出牌狀況 在一個檔案中

//Support 1 player and 1 computer agents: 6 pts.
//Support multiple computer agents: 2 pt.
//Support computer agents with more than 1 level: 2 pt.
//Your presentation: 3 pts.
//Your interface design: 2 pts.
//Any other interesting features: at most 3 pts.
int main(){

	//因應助教程式，index從0開始
	int32_t *card = calloc(105, sizeof(int32_t));
	int32_t player = 0;
	int32_t table_last_index[4] = {0};
	int32_t row_table_point[4] = {0};

	//first, set player == 2
	player = 2;

	//set hand_card
	int32_t **hand_card = declared_two_pointer(player, 10);
	int32_t table[4][5] = {0};
	int32_t player_points[player];
	memset(player_points, 0, sizeof(player_points));

	//player setting (先)
	int32_t agent_level[player-1];
	memset(agent_level, 1, sizeof(agent_level));


#if 0
	//測試 轉變牌的牛頭數函式有沒有問題
	for (int32_t i = 0; i <= 105; i++){
		int32_t temp = CSIE_40771131H_transform(i);
		printf("card: %d, point: %d\n", i, temp);
	}
#endif

	print_table_status(table, 4, 5);


	//隨機配置牌
	range_shuffle(card, 104);


	//qsort(card, 104, sizeof(int32_t), compare);
#if 0
	//測試shuffle有沒有問題
	for (int32_t i = 0 ; i < 104 ; i++){
		if (i != 0 && i % 8 == 0) printf("\n");
		printf("%d \t", card[i]);
	}
	printf("\n");
#endif



	//look up point (what)

	//發牌給每個人
	for (int32_t i = 0 ; i < 10; i++){
		for (int32_t j = 0 ; j < player; j++){
			//printf("card position: %d\n", (i*player+j)+1);
			hand_card[j][i] = card[(i * player + j)];
		}
	}

#if 1
	//檢查hand發放有沒有問題
	for (int32_t i = 0 ; i < player; i++){
		print_player_hand(i+1, hand_card, 10);
	}
#endif

	//放置牌頭
	for (int32_t i = 0 ; i < 4 ; i++)
		table[i][0] = card[10 * player + i];

	print_table_status(table, 4, 5);

	//檢查找牌面每列最後一張牌的函式正常不正常
	CSIE_40771131H_determine_last_index_index(table, table_last_index, row_table_point);
	for (int32_t i = 0 ; i < 4 ; i++)
		printf("%d %d\n", table_last_index[i], row_table_point[i]);


	//function pointer
	int32_t now_card = 0;
	int32_t (*agent_pick[5])(int32_t[4][5], int32_t[10]);
	int32_t (*agent_choose[5])(int32_t[4][5], int32_t);
	agent_pick[0] = Agent_pick_level_1;
	agent_pick[1] = Agent_pick_level_2;
	agent_choose[0] = Agent_choose_level_1;
	agent_choose[1] = Agent_choose_level_2;

	for (int32_t i = 0 ; i < 2 ; i++){
		agent_pick[i](table, hand_card[0]);
		agent_choose[i](table, now_card);
	}


#if 1
	//檢查由數值放位置的函式
	//table[0][1] = hand_card[1][0];
	//table[0][2] = hand_card[1][1];
	//table[0][3] = hand_card[1][2];
	//table[0][4] = hand_card[1][3];
	int32_t choose_card = rand()%10;
	int32_t tp = put_one_card(table, player_points, 1, hand_card[0], hand_card[0][choose_card]);
	printf("res: %d\n", tp);
#endif
	
	int32_t scorepp[2] ={0};
	int32_t lastpp[8] = {0};
	
	CSIE_40771131H_deal(hand_card[0]);
	CSIE_40771131H_pick(table, scorepp, lastpp, hand_card[0]);
	CSIE_40771131H_setup(1);
	printf("id: %d\n", CSIE_40771131H_id);

	free(card);
	free(hand_card);

	return 0;
}

#if 0 
Agent Contest
1-10: 3 pts.
11-20: 2.5 pts.
21-30: 2 pts.
31-40: 1.5 pts.
41-50: 1pt.
Others: 0 pts.
#endif

int32_t CSIE_40771131H_transform(int32_t card){
//根據規則決定牛頭數
	int32_t res = 0;

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
	for (int32_t i = 0 ; i < 10 ; i++){
		CSIE_40771131H_cards[i] = cards[i];
	}
}

//Return the selected card number.
//Table is used to show the current status.
//Score array is the current score status.
//Last array is used to inform the last run cards.
//If the return value is not a valid card, you will lose.
int32_t CSIE_40771131H_pick(const int32_t table[4][5], const int32_t score[2], const int32_t last[8], const int32_t card[10]){
	//取得deal過的資訊
	static int32_t cards[10] = {0}, check = 0;
	if (check ==0){
		extern int32_t CSIE_40771131H_cards[10];
		for (int32_t i = 0;  i<10;i++)
			cards[i] = CSIE_40771131H_cards[i];
	}

	int32_t points[4] = {0}, table_last[4] = {0};
	CSIE_40771131H_determine_last_index_index(table, table_last, points);

	int32_t res = 0, temp = 0;
	while (res == 0){
		temp = rand()%10;
		res = cards[temp];
	}

	cards[temp] = 0;
	check = 1;
	return res;
}


void CSIE_40771131H_determine_last_index_index(const int32_t table[4][5], int32_t last_index[4], int32_t score[4]){
//計算牌面每排最後一個在哪，以及每排牛頭數

	for (int32_t i = 0 ; i < 4 ; i++){
	//第？排
		for (int32_t j = 0 ; j < 5 ; j++){
		//單排牌面狀況
			if (table[i][j] == 0) break;
			last_index[i] = j;
			score[i] += CSIE_40771131H_transform(table[i][j]);
		}
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
	for (int32_t i = 1 ; i < 4 ; i++)
		if (score[i] < score[choose]) choose = i;

	return choose;
}


void __setup_shuffle(int32_t card[], int32_t n){
	for (int32_t i = 0 ; i < n ; i++)
		card[i] = i+1;
}

void range_shuffle(int32_t card[], int32_t n){
//隨機洗牌

	//初始化
	__setup_shuffle(card, n);

	//根據時間調整
	srand(time(0));

	for (int32_t i = n-1 ; i > 0 ; i--){
		int32_t pick = (rand() % (i));
		card[i] ^= card[pick];
		card[pick] ^= card[i];
		card[i] ^= card[pick];
	}

}


//印出指定玩家的手牌
void print_player_hand(int32_t player, int32_t **hand_card, int32_t n){
	static int32_t record = 0;
	if (record == 0)
		printf("ps. 輸出型式：(a,b), a為數值, b為牛頭數\n\n");

	printf("-----第%d位玩家 手牌-----\n", player);

	for (int32_t i = 0 ; i < n ; i++){
		if (i!=0 && i%2==0) printf("\n");
		printf("(%d, %d)\t\t", hand_card[player-1][i], CSIE_40771131H_transform(hand_card[player-1][i]));
	}

	printf("\n");

	record = 1;
}


//印出牌面狀況
void print_table_status(int32_t table[4][5], int32_t row, int32_t col){
	static int32_t record = 0;
	if (record ==0)
		printf("ps. 輸出型式：(a,b), a為數值, b為牛頭數\n\n");

	printf("-----目前牌面-----\n");
	for (int32_t i = 0 ; i < row; i++){
		printf("ROW %d > ", i+1);
		for (int32_t j = 0 ; j < col ; j++){
			printf("(%d, %d)\t\t", table[i][j], CSIE_40771131H_transform(table[i][j]));
		}
		printf("\n");
	}

	record = 1;
}

//用雙重指標創造一個[row][col]的空間，回傳double pointer
int32_t **declared_two_pointer(int32_t row, int32_t col){
	int32_t **two_pointer = calloc(row, sizeof(int32_t *));
	int32_t *__two_pointer[row+5];
	for (int32_t i = 0 ; i < row ; i++){
		__two_pointer[i] = calloc(col+5, sizeof(int32_t));
		two_pointer[i] = __two_pointer[i];
	}

	return two_pointer;
}

//查詢該數值在手牌中的index
//不存在則回傳-1
int32_t look_up_hand_index(int32_t card[10], int32_t val){
	for (int32_t i = 0 ; i < 10 ; i++)
		if (card[i] == val) return i;

	return -1;
}

int32_t pick_one_row(int32_t table[4][5], int32_t score[], int32_t player, int32_t row){
	int32_t points[4] = {0}, table_last[4] = {0};
	CSIE_40771131H_determine_last_index_index(table, table_last, points);

	score[player-1] += points[row];
	memset(table[row], 0, 5 * sizeof(int32_t));
}

int32_t Agent_pick_level_1(int32_t table[4][5], int32_t card[10]){}
int32_t Agent_choose_level_1(int32_t table[4][5], int32_t card){}
int32_t Agent_pick_level_2(int32_t table[4][5], int32_t card[10]){}
int32_t Agent_choose_level_2(int32_t table[4][5], int32_t card){}

//之後要check數值, 使用者有可能輸入不存在的手牌
//直接在讓使用者輸入的function檢查就好
int32_t put_one_card(int32_t table[4][5], int32_t score[], int32_t player, int32_t card[10], int32_t val){
	int32_t points[4] = {0}, table_last[4] = {0};
	CSIE_40771131H_determine_last_index_index(table, table_last, points);

	last_status status[4];

	for (int32_t i = 0 ; i < 4; i ++)
		status[i] = (last_status){ table[i][table_last[i]] , i };

	qsort(status, 4, sizeof(last_status), compare);

	int32_t res = -1;
	for (int32_t i = 0 ; i < 4; i ++)
		if (status[i].last < val) res = status[i].row;

	if (res != -1){
		if (table_last[res] >= 4){
			memset(table[res], 0, 5 * sizeof(int32_t));
			table[res][0] = val;
			print_table_status(table, 4, 5);
			printf("< new message >\n");
			printf("Player %d－－Pick row: %d, row points: %d, new title: %d\n", player, res+1, points[res], val);
			score[player-1] += points[res];
			if (put_one_card_and_clear_hand(card, val) == -1){
				printf("< new message >\n");
				printf("Your hand card don't exist the value.\n");
			}
		}else if (table_last[res] >= 0){
			put_one_card_in_table_row(table, player, card, val, res, table_last);
		}
	}
	//look_up_hand_index(card, val);

	//if return -1, the player should choose one row to pick
	return res;
}

int32_t put_one_card_and_clear_hand(int32_t card[10], int32_t val){
	int32_t temp = look_up_hand_index(card, val);
	if (temp != -1){
		card[look_up_hand_index(card, val)] = 0;
		return 1;
	}else return -1;
}


//add_card in table row
int32_t put_one_card_in_table_row(int32_t table[4][5], int32_t player, int32_t card[10], int32_t val, int32_t row, int32_t table_last[]){
	int32_t put_col = table_last[row] + 1;
	int32_t index_val_in_hand = look_up_hand_index(card, val);
	if (index_val_in_hand == -1)
		printf("The card don't exist in the player %d hand\n", player);

	printf("< new message >\n");
	printf("Player %d－－put a card (%d, %d) in row %d, col %d\n", player, val, CSIE_40771131H_transform(val), row+1, table_last[row] +1);

	table[row][put_col] = val;
	card[index_val_in_hand] = 0;

	print_table_status(table, 4, 5);
}

void print_meau_stat_game(){
	int32_t count = 0;
	printf("【誰是牛頭王】\n");
	printf("%d) 開始遊戲\n", ++count);
	printf("%d) 讀取進度\n", ++count);
	printf("%d) 結束遊戲\n", ++count);
	printf("-----------------------");
}

void print_meau_game_setting(){
	int32_t count = 0;
	printf("【遊戲設定】\n");
	printf("%d) 規則設定\n", ++count);
	printf("%d) 遊戲人數\n", ++count);
	printf("%d) 等級設定\n", ++count);
	printf("%d) 對局開始！\n", ++count);
	printf("%d) 回上一頁！\n", ++count);
	printf("-----------------------");

}

//received player number and level setting
void print_meau_agent_setting(int32_t number, int32_t level[]){
	int32_t i = 0 ;
	printf("【電腦強度設定】\n");
	for (i = 1 ; i < number ; i++){
		printf("%d) Agent: %d／level: %d\n", i, i, level[i-1]);

	}
	printf("%d) 回上一頁！\n", i);
	printf("-----------------------");

}

void print_meau_store(){
	int32_t count = 0;
	printf("【儲存介面】\n");
	printf("%d) 繼續遊戲\n", ++count);
	printf("%d) 結束遊戲\n", ++count);
	printf("-----------------------");
}

//input card
void print_meau_sort_hand(){
	int32_t count = 0;
	printf("【手牌處理介面】\n");
	printf("%d) (主)手牌小→ 大\n", ++count);
	printf("%d) (主)手牌大→ 小\n", ++count);
	printf("%d) (主)牛頭數大→ 小／(次)手牌小→ 大\n", ++count);
	printf("%d) (主)牛頭數小→ 大／(次)手牌小→ 大\n", ++count);
	printf("-----------------------");
}

//可以寫進去print_meau內 (再一個函式

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void CSIE_40771131H_setup(int32_t id);
void CSIE_40771131H_deal(const int32_t cards[10]);
int32_t CSIE_40771131H_pick(const int32_t table[4][5], const int32_t score[2], const int32_t last[8], const int32_t card[10]);
int32_t CSIE_40771131H_choose(const int32_t table[4][5], int32_t card);

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

int32_t put_one_card(int32_t table[4][5], int32_t score[], int32_t player, int32_t card[10], int32_t val);
int32_t put_one_card_and_clear_hand(int32_t card[10], int32_t val);
int32_t put_one_card_in_table_row(int32_t table[4][5], int32_t player, int32_t card[10], int32_t val, int32_t row, int32_t table_last[]);

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

int main(){

	int32_t *card = calloc(105, sizeof(int32_t));
	int32_t player = 0;
	int32_t table_last_index[4] = {0};
	int32_t row_table_point[4] = {0};

	player = 2;

	int32_t **hand_card = declared_two_pointer(player, 10);
	int32_t table[4][5] = {0};
	int32_t player_points[player];
	memset(player_points, 0, sizeof(player_points));

	int32_t agent_level[player-1];
	memset(agent_level, 1, sizeof(agent_level));


	range_shuffle(card, 104);


	//發牌給每個人
	for (int32_t i = 0 ; i < 10; i++){
		for (int32_t j = 0 ; j < player; j++){
			//printf("card position: %d\n", (i*player+j)+1);
			hand_card[j][i] = card[(i * player + j)];
		}
	}

	//放置牌頭
	for (int32_t i = 0 ; i < 4 ; i++)
		table[i][0] = card[10 * player + i];


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

	free(card);
	free(hand_card);

	return 0;
}

int32_t CSIE_40771131H_transform(int32_t card){
	int32_t res = 0;
	if (card == 0 || card == -1) return 0;
	else if (card < 0 || card > 104) return -1;

	switch (card){
		case 5: case 15: case 25: case 35: case 45: case 65: case 75: case 85: case 95: 
			return 2;

		case 10: case 20: case 30: case 40: case 50: case 60: case 70: case 80: case 90: case 100: 
			return 3;

		case 11: case 22: case 33: case 44: case 66: case 77: case 88: case 99:
			return 5;

		case 55:
			return 7;

		default: 
			return 1; 
	}

}

void CSIE_40771131H_setup(int32_t id){
	extern int32_t CSIE_40771131H_id;
	CSIE_40771131H_id = id;
}

void CSIE_40771131H_deal(const int32_t cards[10]){
	extern int32_t CSIE_40771131H_cards[10];
	for (int32_t i = 0 ; i < 10 ; i++){
		CSIE_40771131H_cards[i] = cards[i];
	}
}

int32_t CSIE_40771131H_pick(const int32_t table[4][5], const int32_t score[2], const int32_t last[8], const int32_t card[10]){
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

	for (int32_t i = 0 ; i < 4 ; i++){
		for (int32_t j = 0 ; j < 5 ; j++){
			if (table[i][j] == 0) break;
			last_index[i] = j;
			score[i] += CSIE_40771131H_transform(table[i][j]);
		}
	}
}

int32_t CSIE_40771131H_choose(const int32_t table[4][5], int32_t card){
	int32_t score[4] = {0}, table_last[4] = {0};

	CSIE_40771131H_determine_last_index_index(table, table_last, score);

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
	__setup_shuffle(card, n);
	srand(time(0));

	for (int32_t i = n-1 ; i > 0 ; i--){
		int32_t pick = (rand() % (i));
		card[i] ^= card[pick];
		card[pick] ^= card[i];
		card[i] ^= card[pick];
	}

}


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

int32_t **declared_two_pointer(int32_t row, int32_t col){
	int32_t **two_pointer = calloc(row, sizeof(int32_t *));
	int32_t *__two_pointer[row+5];
	for (int32_t i = 0 ; i < row ; i++){
		__two_pointer[i] = calloc(col+5, sizeof(int32_t));
		two_pointer[i] = __two_pointer[i];
	}

	return two_pointer;
}

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

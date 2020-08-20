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

int32_t User_pick(int32_t table[4][5], int32_t card[10]);
int32_t User_choose(int32_t table[4][5], int32_t card);


int32_t Agent_pick_level_1(int32_t table[4][5], int32_t card[10]);
int32_t Agent_choose_level_1(int32_t table[4][5], int32_t card);
int32_t Agent_pick_level_2(int32_t table[4][5], int32_t card[10]);
int32_t Agent_choose_level_2(int32_t table[4][5], int32_t card);

void pick_one_row(int32_t table[4][5], int32_t score[], int32_t player, int32_t row);

//if return -1, player should choose one row to pick
int32_t put_one_card(int32_t table[4][5], int32_t score[], int32_t player, int32_t card[10], int32_t val);
int32_t put_one_card_and_clear_hand(int32_t card[10], int32_t val);
int32_t put_one_card_in_table_row(int32_t table[4][5], int32_t player, int32_t card[10], int32_t val, int32_t row, int32_t table_last[]);

void list_rank(int32_t score[], int32_t set_points, int32_t player_number);
void init_all_val();
void init_game_start_table_and_hand(int32_t *card, int32_t table[4][5], int32_t **hand_card, int32_t player_number);
int32_t count_hand_card(int32_t *card);
void sort_hand_card(int32_t *card, int32_t choose);


//print meau
void print_meau_start_game();
void print_meau_game_setting();
void print_meau_agent_setting();
void print_meau_store();
void print_meau_sort_hand();
void print_meau_choose();

int32_t win[2] = {0};

void swap(int32_t *a, int32_t *b){
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

typedef struct _last_status{
	int32_t last;
	int32_t row;
}last_status;

int32_t compare(const void *a, const void *b){
	if (((last_status *) a)->last > ((last_status *)b)->last) return 1;
	return 0;
}

int32_t compare_card_inc(const void *a, const void *b){
	if (*((int32_t *) a) > *((int32_t *) b)) return 1;
	return 0;
}

int32_t compare_card_dec(const void *a, const void *b){
	if (*((int32_t *) a) < *((int32_t *) b)) return 1;
	return 0;
}

int32_t CSIE_40771131H_cards[10] = {0};
int32_t CSIE_40771131H_id = 0;
int32_t CSIE_40771131H_choose_max  = 0; 


//因應助教程式，index從0開始
int32_t *card;

//first, set player == 2
int32_t table_last_index[4] = {0}, row_table_point[4] = {0};
int32_t player = 2;
int32_t start_game_choose = 0, game_setting = 0, set_points = 172;
int32_t meau_choose = 0, meau_store = 0;
int32_t choose_hand_user = 0, sort_hand = 0;

//set hand_card
int32_t **hand_card;
int32_t table[4][5] = {0};
int32_t player_points[10] = {0};

//player setting (先)
int32_t agent_level[10] = {1};

int32_t read_input(char *str);
void start_a_game(int32_t choose);

//function pointer
int32_t (*agent_pick[10])(int32_t[4][5], int32_t[10]);
int32_t (*agent_choose[10])(int32_t[4][5], int32_t);


//設定電腦強度
void set_agent_level();


//Support 1 player and 1 computer agents: 6 pts.
//Support multiple computer agents: 2 pt.
//Support computer agents with more than 1 level: 2 pt.
//Your presentation: 3 pts.
//Your interface design: 2 pts.
//Any other interesting features: at most 3 pts.
int main(){

	hand_card = declared_two_pointer(player, 10);
	card = calloc(105, sizeof(int32_t));

	print_table_status(table, 4, 5);
	init_game_start_table_and_hand(card, table, hand_card, player);
	print_player_hand(1, hand_card, 10); 

	for (int32_t i = 0 ; i < 1001; i++){
		start_a_game(0);
	}

	double all = win[0] + win[1];
	printf("Player1: %.2lf\n", (double)win[0]/all);
	printf("Player2: %.2lf\n", (double)win[1]/all);


	/*
	   int32_t now_card = 0;
	   for (int32_t i = 0 ; i < 2 ; i++){
	   agent_pick[i](table, hand_card[0]);
	   agent_choose[i](table, now_card);
	   }
	 */

#if 0

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

	sort_hand_card(hand_card[0], 1);
	print_player_hand(1, hand_card, 10); 
	sort_hand_card(hand_card[0], 2);
	print_player_hand(1, hand_card, 10); 
	sort_hand_card(hand_card[0], 3);
	print_player_hand(1, hand_card, 10); 
	sort_hand_card(hand_card[0], 4);
	print_player_hand(1, hand_card, 10); 

	int32_t rank_score[10] = {171, 171, 40, 34, 85, 34, 92, 10, 23, 10};
	list_rank(rank_score, 80, 10);
	start_a_game(0);
#endif

	free(card);
	free(hand_card);



	return 0;
}

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

	qsort(status, 4, sizeof(last_status), compare);
	/*
	   for (int32_t i = 0 ; i < 4; i++){
	   printf("last:%d, row:%d\n", status[i].last, status[i].row);
	   }
	 */

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

int32_t Agent_pick_level_1(int32_t table[4][5], int32_t card[10]){
	int32_t res = 0, temp = 0;

	int32_t count = 0;

	while (res == 0 || res == -1){
		temp = rand()%10;
		res = card[temp];
		count+=1;
	}
	int32_t last[8] = {0};
	return res;
}

int32_t Agent_choose_level_1(int32_t table[4][5], int32_t card){
	CSIE_40771131H_choose(table, card);
	return CSIE_40771131H_choose_max;
}



int32_t Agent_pick_level_2(int32_t table[4][5], int32_t card[10]){
	return Agent_pick_level_1(table, card);
}


int32_t Agent_choose_level_2(int32_t table[4][5], int32_t card){
	return rand()%4;
}

//暫時
int32_t Agent_pick_level_3(int32_t table[4][5], int32_t card[10]){
	int32_t last[8] = {0};
	return CSIE_40771131H_pick(table, player_points, last, card);
}

int32_t Agent_choose_level_3(int32_t table[4][5], int32_t card){
	return CSIE_40771131H_choose(table, card);
}

int32_t User_pick(int32_t table[4][5], int32_t card[10]){}
int32_t User_choose(int32_t table[4][5], int32_t card){}


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
		int32_t pick = rand() % i;
		card[i] ^= card[pick];
		card[pick] ^= card[i];
		card[i] ^= card[pick];
	}
}


//印出指定玩家的手牌
void print_player_hand(int32_t player, int32_t **hand_card, int32_t n){
	static int32_t record = 0;
	if (record == 0){
		printf("ps. 輸出型式：(a,b), a為數值, b為牛頭數\n\n");
		record = 1;
	}

	printf("-----第%d位玩家 手牌-----\n", player);

	for (int32_t i = 0 ; i < n ; i++){
		if (i!=0 && i%2==0) printf("\n");
		printf("(%d, %d)\t\t", hand_card[player-1][i], CSIE_40771131H_transform(hand_card[player-1][i]));
	}

	printf("\n");
}


//印出牌面狀況
void print_table_status(int32_t table[4][5], int32_t row, int32_t col){
	int32_t points[4] = {0}, table_last[4] = {0};
	CSIE_40771131H_determine_last_index_index(table, table_last, points);
	static int32_t record = 0;
	if (record ==0){
		printf("ps. 輸出型式：(a,b), a為數值, b為牛頭數\n\n");
		record = 1;
	}

	printf("-----目前牌面-----\n");
	for (int32_t i = 0 ; i < row; i++){
		printf("ROW %d > ", i+1);
		for (int32_t j = 0 ; j < col ; j++)
			printf("(%d, %d)\t\t", table[i][j], CSIE_40771131H_transform(table[i][j]));
		printf("|排尾位置：%d, 總牛頭數: %d\n", table_last[i]+1, points[i]);
	}
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

void pick_one_row(int32_t table[4][5], int32_t score[], int32_t player, int32_t row){
	int32_t points[4] = {0}, table_last[4] = {0};
	CSIE_40771131H_determine_last_index_index(table, table_last, points);

	score[player-1] += points[row];
	memset(table[row], 0, sizeof(table[row]));
}



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
			memset(table[res], 0, sizeof(table[res]));
			table[res][0] = val;
			//printf("< new message >\n");
			printf("Player %d－－Pick row: %d, row points: %d, new title: %d\n", player, res+1, points[res], val);

			int32_t cur_point = score[player-1];


			score[player-1] += points[res];

			printf("now: point %d(+%d)\n", score[player-1], score[player-1] - cur_point);

			if (put_one_card_and_clear_hand(card, val) == -1){
				printf("< new message >\n");
				printf("Your hand card don't exist the value.\n");
			}
		}else if (table_last[res] >= 0)
			put_one_card_in_table_row(table, player, card, val, res, table_last);
	}

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
	if (index_val_in_hand == -1){
		printf("The card don't exist in the player %d hand\n", player);
		return -1;
	}

	//printf("< new message >\n");
	printf("Player %d－－put a card (%d, %d) in row %d, col %d\n", player, val, CSIE_40771131H_transform(val), row+1, table_last[row] +1);

	table[row][put_col] = val;
	card[index_val_in_hand] = 0;

	return 1;
}

void print_meau_start_game(){
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
	printf("%d) 回上一頁\n", ++count);
	printf("-----------------------");
}


void print_meau_choose(){
	int32_t count = 0;
	printf("【選牌 & 選列介面】\n");
	printf("%d) 選牌\n", ++count);
	printf("%d) 列出牌面\n", ++count);
	printf("%d) 出過的手牌\n", ++count);
	printf("%d) 查詢牛頭數\n", ++count);
	printf("%d) 儲存進度\n", ++count);
	printf("-----------------------");
}

void list_rank(int32_t score[], int32_t set_points, int32_t player_number){
	struct sort{
		int32_t win_num;
		int32_t index;
		int32_t rank;
	}win_point[player_number], temp;

	memset(win_point, 1000, sizeof(win_point));

	for (int32_t i = 0 ; i < player_number ; i++){
		int32_t a = score[i], b = 10000;
		if (score[i] - set_points >=0) b = -1 * score[i];
		win_point[i].win_num = a < b ? a : b;
		win_point[i].index = i;
	}

	for (int32_t i = 0 ; i < player_number ; i++)
		for (int32_t j = 1; j < player_number ; j++)
			if (win_point[j-1].win_num > win_point[j].win_num){
				temp = win_point[j-1];
				win_point[j-1] = win_point[j];
				win_point[j] = temp;
			}

	printf("【排名狀況");
	if (set_points != 172) printf("－－狂牛局】\n");
	else printf("－－普通局】\n");

	for (int32_t i = 0 ; i < player_number; i++){
		win_point[i].rank= i+1;

		if (i != 0 && (win_point[i].win_num == win_point[i-1].win_num))
			win_point[i].rank = win_point[i-1].rank;

		printf("|\tRank %d\t\tPlayer %d\t\tPoints: %d\t| ", win_point[i].rank, win_point[i].index + 1, score[win_point[i].index]);
		if (score[win_point[i].index] >= set_points) printf("(感染者)\n");
		else puts("");
	}

	printf("----------------------------\n");
	if (set_points != 172) printf(">>>感染標準：%d\n", set_points);

	if (win_point[0].rank == win_point[1].rank){
		win[0] += 1;
		win[1] += 1;
	}else if (win_point[0].rank < win_point[1].rank) win[win_point[0].index]+=1;
	else if (win_point[0].rank > win_point[1].rank) win[win_point[1].index]+=1;
}

//全部初始化
void init_all_val(){
	for (int32_t i = 0 ; i < 105 ; i++){
		card[i] = 0;
		if (i < 10){
			agent_level[i] = 1;
			if (i < 4){
				table_last_index[i] = 0;
				row_table_point[i] = 0;
			}
			player_points[i] = 0;
		}

	}
	//agent_level[0] = 0;
	player = 2;
	start_game_choose = 0;
	game_setting = 0;
	set_points = 172;
	meau_choose = 0;
	meau_store = 0;
	choose_hand_user = 0;
	sort_hand = 0;
}

//發牌與牌面配置
void init_game_start_table_and_hand(int32_t *card, int32_t table[4][5], int32_t **hand_card, int32_t player_number){


	//隨機配置牌
	range_shuffle(card, 104);

	//發牌給每個人
	for (int32_t i = 0 ; i < 10; i++)
		for (int32_t j = 0 ; j < player_number; j++){
			hand_card[j][i] = card[(i * player_number + j)];
		}

	//放置牌頭
	for (int32_t i = 0 ; i < 4 ; i++)
		table[i][0] = card[10 * player_number + i];

}

//計算手牌數量
int32_t count_hand_card(int32_t *card){
	int32_t count = 0;
	for (int32_t i = 0 ; i < 10 ; i++)
		if (!(card[i] == 0 || card[i] == -1)) count+=1;
	return count;
}


//choose 1: num 小到大
//choose 2: num 大到小
//choose 3: point 大到小
//choose 4: point 小到大
void sort_hand_card(int32_t card[], int32_t choose){

	if (choose != 2) qsort(card, 10, sizeof(int32_t), compare_card_inc);
	else qsort(card, 10, sizeof(int32_t), compare_card_dec);

	int32_t point[10] = {0};

	for (int32_t i = 0 ; i < 10 ; i++)
		point[i] = CSIE_40771131H_transform(card[i]);

	if (choose != 2 && choose !=1){
		int32_t (*compare)(const void *a, const void *b);

		if (choose == 4) compare = compare_card_inc;
		else if (choose == 3) compare = compare_card_dec;

		for (int32_t i = 0 ; i < 10 ; i++)
			for (int32_t j = 1; j < 10 ; j++)
				if (compare((const void *)&point[j-1], (const void*)&point[j])){
					swap(&point[j-1], &point[j]);
					swap(&card[j-1], &card[j]);
				}
	}
}

int32_t read_input(char *str){
	int32_t temp = 0 ;
	printf("--------------\n");
	printf("%s\n", str);
	printf("Choose: ");
	scanf("%d", &temp);
	return temp;
}

//choose 0 => new
//choose 1 => load
void start_a_game(int32_t choose){
	if (choose == 0){
		init_all_val();
		//
		player = 2;
		int32_t **hand_card_ptr = hand_card;
		hand_card = declared_two_pointer(player, 10);
		init_game_start_table_and_hand(card, table, hand_card, player);
		free(hand_card_ptr);


		//for (int32_t i = 0 ; i < 5 ; i++)
		//agent_level[i] = 2;
		agent_level[1] = 3;
		agent_level[0] = 1;


		//先讓使用者設定強度
		set_agent_level();
	}else if (choose == 1){

	}

	int32_t last[8] = {0};

	print_table_status(table, 4, 5);
	while (count_hand_card(hand_card[0]) != 0){
		CSIE_40771131H_determine_last_index_index(table, table_last_index , row_table_point);
		int32_t record_card[10] = {0};
		int32_t player_list[10] = {0};

		printf("< new message >\n");
		for (int32_t i = 0 ; i < player; i++){
			//sleep(1);
			//int32_t choose_card = CSIE_40771131H_pick(table, player_points, last, hand_card[i]);
			int32_t choose_card = agent_pick[i](table, hand_card[i]);

			record_card[i] = hand_card[i][look_up_hand_index(hand_card[i], choose_card)];
			player_list[i] = i;
			printf("Player %d－－put a card (%d, %d) on the table\n", i+1, record_card[i], CSIE_40771131H_transform(record_card[i]));
		}
		for (int32_t i = 0 ; i < player; i++)
			for (int32_t j = 1 ; j < player ; j++)
				if (record_card[j-1] > record_card[j]){
					swap(&record_card[j-1], &record_card[j]);
					swap(&player_list[j-1], &player_list[j]);
				}

		printf("Enter...\n");
		system("clear");

		for (int32_t i = 0 ; i < player ; i++){
			printf("【牌局戰況】\n");
			printf("< new message >\n");
			int32_t temp = put_one_card(table, player_points, player_list[i]+1, hand_card[player_list[i]], record_card[i]);
			if (temp == -1){
				//int32_t res_row = CSIE_40771131H_choose(table, record_card[i]);
				int32_t res_row = agent_choose[player_list[i]](table, record_card[i]);


				CSIE_40771131H_determine_last_index_index(table, table_last_index , row_table_point);
				printf("Player %d－－Pick row: %d, row points: %d, new title: %d\n", player_list[i]+1, res_row+1, row_table_point[res_row], record_card[i]);
				int32_t now_point = player_points[player_list[i]];
				pick_one_row(table, player_points, player_list[i]+1, res_row);
				put_one_card_and_clear_hand(hand_card[player_list[i]], record_card[i]);

				int32_t cur_point = player_points[player_list[i]];
				printf("now: point %d(+%d)\n", cur_point, cur_point - now_point);
				//important!!
				table[res_row][0] = record_card[i];

			}
			printf("Enter...\n");
			system("clear");
		}
	}

	printf("\n\n");
	list_rank(player_points, set_points, player);

}

void set_agent_level(){
	for (int32_t i = 0 ; i < 10 ; i++){
		if (agent_level[i] == 0){
			agent_pick[i] = User_pick;
			agent_choose[i] = User_choose;
		}else if (agent_level[i] == 1){
			agent_pick[i] = Agent_pick_level_1;
			agent_choose[i] = Agent_choose_level_1;
		}else if (agent_level[i] == 2){
			agent_pick[i] = Agent_pick_level_2;
			agent_choose[i] = Agent_choose_level_2;
		}else if (agent_level[i] == 3){
			agent_pick[i] = Agent_pick_level_3;
			agent_choose[i] = Agent_choose_level_3;

		}else
			printf("error!\n");
	}
}

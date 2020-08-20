#include "40771131H_contest.h"

void __setup_shuffle(int32_t card[], int32_t n);
void range_shuffle(int32_t card[], int32_t n);
void print_player_hand(int32_t player, int32_t **hand_card, int32_t n);
void print_table_status(int32_t table[4][5], int32_t row, int32_t col);
int32_t **declared_two_pointer(int32_t row, int32_t col);
int32_t look_up_hand_index(int32_t card[10], int32_t val);

int32_t User_pick(int32_t table[4][5], int32_t card[10]);
int32_t User_choose(int32_t table[4][5], int32_t card);

void store_now_progress();
int32_t load_now_progress();

int32_t read_input(char *str);


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

//設定電腦強度
void set_agent_level();


//print meau
void print_meau_start_game();
void print_meau_game_setting();
void print_meau_agent_setting();
void print_meau_store();
void print_meau_sort_hand();
void print_meau_choose();

int32_t read_input(char *str);
void start_a_game(int32_t choose);


void start_setting_function();

void swap(int32_t *a, int32_t *b){
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

int32_t compare_card_inc(const void *a, const void *b){
	if (*((int32_t *) a) > *((int32_t *) b)) return 1;
	return 0;
}

int32_t compare_card_dec(const void *a, const void *b){
	if (*((int32_t *) a) < *((int32_t *) b)) return 1;
	return 0;
}



//因應助教程式，index從0開始
int32_t *card;

//first, set player == 2
int32_t table_last_index[4] = {0}, row_table_point[4] = {0};
int32_t player = 2;
int32_t start_game_choose = 0, game_setting = 0, set_points = 172;
int32_t meau_choose = 0, meau_store = 0;
int32_t choose_hand_user = 0, sort_hand = 0;
int32_t User_pick_one_record_num = 0;
int32_t User_pick_and_choose_num = 0;

//set hand_card
int32_t **hand_card;
int32_t table[4][5] = {0};
int32_t player_points[10] = {0};

//player setting (先)
int32_t agent_level[10] = {1};


//function pointer
int32_t (*agent_pick[10])(int32_t[4][5], int32_t[10]);
int32_t (*agent_choose[10])(int32_t[4][5], int32_t);


//Support 1 player and 1 computer agents: 6 pts.
//Support multiple computer agents: 2 pt.
//Support computer agents with more than 1 level: 2 pt.
//Your presentation: 3 pts.
//Your interface design: 2 pts.
//Any other interesting features: at most 3 pts.
int main(){

	hand_card = declared_two_pointer(player, 1);
	card = calloc(105, sizeof(int32_t));

	start_setting_function();

	return 0;
}





//等級一 random出牌
int32_t Agent_pick_level_1(int32_t table[4][5], int32_t card[10]){
	int32_t res = 0, temp = 0;

	int32_t count = 0;

	while (res == 0 || res == -1){
		temp = rand()%10;
		res = card[temp];
		count+=1;
	}
	//int32_t last[8] = {0};
	return res;
}


//等級一 優先吃最多牛頭的牌
int32_t Agent_choose_level_1(int32_t table[4][5], int32_t card){
	CSIE_40771131H_choose(table, card);
	return CSIE_40771131H_choose_max;
}

//等級二 出牌同等級一
int32_t Agent_pick_level_2(int32_t table[4][5], int32_t card[10]){
	return Agent_pick_level_1(table, card);
}


//等級二 吃牌隨機選
int32_t Agent_choose_level_2(int32_t table[4][5], int32_t card){
	return rand()%4;
}


//等級三 優先出不會爆的牌
int32_t Agent_pick_level_3(int32_t table[4][5], int32_t card[10]){
	int32_t last[8] = {0};
	return CSIE_40771131H_pick(table, player_points, last, card);
}


//等級三 優先吃最少牛頭數的牌
int32_t Agent_choose_level_3(int32_t table[4][5], int32_t card){
	return CSIE_40771131H_choose(table, card);
}


//等級零：給使用者選牌
int32_t User_pick(int32_t table[4][5], int32_t card[10]){
	static int32_t count = 0;
	static int32_t last[10] = {0};

	meau_choose = 0;
	while (1){
		system("clear");
		if (User_pick_and_choose_num == 1){
			printf("< new message >\n");
			printf(">> 您的牌比牌面上都還要小\n");
			printf(">> 需要選擇想拿走的一列\n\n");
			printf("目前手牌 >> %d\n\n", User_pick_one_record_num);
		}

		print_meau_choose();
		meau_choose = read_input("請輸入數字\n");
	
		//儲存進度
		if (meau_choose == 5){
			meau_store = 0;
			while (1){
				system("clear");
				store_now_progress();
				printf("< 進度已儲存 >\n");

				print_meau_store();
				//進度儲存的函式
				meau_store= read_input("請輸入數字\n");
				if (meau_store == 1) break;
				else if (meau_store == 2){
					return -1;
				}else printf("You input error!\n");
			}
		
		//秀出牌面
		}else if (meau_choose == 2){
			system("clear");
			print_table_status(table, 4, 5);

			printf("Enter...\n");
			getchar();
			getchar();

		//查詢出過的牌
		}else if (meau_choose == 3){
			system("clear");
			printf("(僅紀錄您開啟遊戲後當次的出牌紀錄)\n");
			printf("您出過的牌\n>>>");
			for (int32_t i = 0 ; i < count ; i++){
				printf("(%d, %d)\t", last[i], CSIE_40771131H_transform(last[i]));
			}
			puts("");

			printf("Enter...\n");
			getchar();
			getchar();

		//查詢牛頭數
		}else if (meau_choose == 4){
			system("clear");
			printf("請輸入數值(無效值為—1, 0)\n>>>");
			int32_t temp_look_up = 0;
			scanf("%d", &temp_look_up);
			printf("查詢牛頭數:%d\n", CSIE_40771131H_transform(temp_look_up));

			printf("Enter...\n");
			getchar();
			getchar();
		}else if (meau_choose == 1){
			int32_t hand_meau_record = 0;

			while (1){

start_choose_1:
				system("clear");
				print_table_status(table, 4, 5);

				printf("\n< 手牌資訊 >\n");
				print_player_hand(1, hand_card, 10);

				if (User_pick_and_choose_num == 1)
					printf("\n目前手牌 >> %d\n", User_pick_one_record_num);

				printf("-----------------\n");

				printf("1) 排序手牌\n");
				if (User_pick_and_choose_num == 0)
					printf("2) 出牌選擇\n");
				else printf("2) 選擇要拿走的列\n");

				hand_meau_record = read_input("請輸入數字\n");

				//排序手牌
				if (hand_meau_record == 1){
					system("clear");
					print_meau_sort_hand();
					while (1){
						sort_hand = read_input("請輸入數字\n");
						if (sort_hand == 5) break;
						else if (sort_hand > 5 || sort_hand < 1)
							printf("Input error!\n");
						else{
							sort_hand_card(card, sort_hand);
							break;
						}
					}
				//決定出牌
				}else if (hand_meau_record == 2){
					int32_t choose_card_num = 0;
					if (User_pick_and_choose_num == 0){
						while (1){
							choose_card_num = read_input("請輸入想出的牌面\n");
							int32_t look_up_hand_num = look_up_hand_index(card, choose_card_num);
							if (look_up_hand_num == -1) printf("input error!\n");
							else{
								int32_t double_check = 0;
								while (1){
									system("clear");
									print_table_status(table, 4, 5);
									printf("\n您選擇的手牌為：%d\n", choose_card_num);
									printf("1) 確定\n");
									printf("2) 回上一頁\n");
									double_check = read_input("請輸入數字\n");
									if (double_check == 1){
										last[count++] = choose_card_num;
										return choose_card_num;
									}else if (double_check == 2) goto start_choose_1;
									else printf("Input error!\n");
								}
							}
						}
					}else{
						//choose
						int32_t User_pick_row_index = 0;
						User_pick_row_index = read_input("請輸入ROW值\n");
						while (1){
							if (User_pick_row_index <= 0 && User_pick_row_index > 4)
								printf("Input error!\n");
							else return User_pick_row_index-1;
						}
					}
				}else printf("input error!\n");
			}
		}else printf("Input error!\n");

		if (meau_choose == 5 && meau_store == 2) break;
	}
}

//讓使用者選擇要吃的排，介面跟pick差不多
int32_t User_choose(int32_t table[4][5], int32_t card){

	User_pick_one_record_num = card;
	User_pick_and_choose_num = 1;

	return User_pick(table, hand_card[0]);
}



void __setup_shuffle(int32_t card[], int32_t n){
	for (int32_t i = 0 ; i < n ; i++)
		card[i] = i+1;
}

//隨機洗牌
void range_shuffle(int32_t card[], int32_t n){

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
		printf("(%3d, %3d )\t\t", hand_card[player-1][i],CSIE_40771131H_transform(hand_card[player-1][i]));
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
			printf("(%3d, %3d )\t", table[i][j], CSIE_40771131H_transform(table[i][j]));
		printf("|排尾位置：%3d, 總牛頭數: %3d\n", table_last[i]+1, points[i]);
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


//吃掉一整排
void pick_one_row(int32_t table[4][5], int32_t score[], int32_t player, int32_t row){
	int32_t points[4] = {0}, table_last[4] = {0};
	CSIE_40771131H_determine_last_index_index(table, table_last, points);

	score[player-1] += points[row];
	memset(table[row], 0, sizeof(table[row]));
}



//放一張牌在桌面上
int32_t put_one_card(int32_t table[4][5], int32_t score[], int32_t player, int32_t card[10], int32_t val){
	int32_t points[4] = {0}, table_last[4] = {0};
	CSIE_40771131H_determine_last_index_index(table, table_last, points);

	CSIE_40771131H_last_status status[4];

	for (int32_t i = 0 ; i < 4; i ++)
		status[i] = (CSIE_40771131H_last_status){ table[i][table_last[i]] , i };

	qsort(status, 4, sizeof(CSIE_40771131H_last_status), CSIE_40771131H_compare);

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

			printf("now: point %d  ( + %d )\n", score[player-1], score[player-1] - cur_point);

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

//給予數值，刪除手牌中的該手牌
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

	printf("Player %d－－put a card (%d, %d) in row %d, col %d\n", player, val, CSIE_40771131H_transform(val), row+1, table_last[row] +1);

	table[row][put_col] = val;
	card[index_val_in_hand] = 0;

	return 1;
}


//print 介面
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

//秀出排名狀況
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

}

//全部初始化
void init_all_val(){
	for (int32_t i = 0 ; i < 105 ; i++){
		card[i] = 0;
		if (i < 10){
			agent_level[i] = 1;
			player_points[i] = 0 ;
			if (i < 4){
				table_last_index[i] = 0;
				row_table_point[i] = 0;
			}
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


//store progress
void store_now_progress(){
	FILE *pfile = NULL;

	if ((pfile = fopen("40771131H_project_store.txt", "w")) ==NULL){
		perror("Error: ");
		return ;
	}

	fprintf(pfile, "[player]%d\n", player);
	fprintf(pfile, "[set_points]%d\n", set_points);
	fprintf(pfile, "[meau_choose]%d\n", meau_choose);
	fprintf(pfile, "[meau_store]%d\n", meau_store);
	fprintf(pfile, "[start_game_choose]%d\n", start_game_choose);
	fprintf(pfile, "[game_setting]%d\n", game_setting);
	fprintf(pfile, "[sort_hand]%d\n", sort_hand);
	fprintf(pfile, "[choose_hand_user]%d\n", choose_hand_user);

	fprintf(pfile, "[table]\n");
	for (int32_t i = 0; i < 4; i++)
		for (int32_t j = 0 ; j < 5; j++)
			fprintf(pfile, "%d ", table[i][j]);
	fprintf(pfile, "\n");

	fprintf(pfile, "[agent_level]\n");
	for (int32_t i = 0 ; i < 10 ; i++){
		fprintf(pfile, "%d ", agent_level[i]);
	}
	fprintf(pfile, "\n");

	fprintf(pfile, "[player_points]\n");
	for (int32_t i = 0 ; i < 10 ; i++){
		fprintf(pfile, "%d ", player_points[i]);
	}
	fprintf(pfile, "\n");

	fprintf(pfile, "[hand_card]\n");
	for (int32_t i = 0 ; i < player ; i++){
		for (int32_t j = 0 ; j < 10 ; j++)
			fprintf(pfile, "%d ", hand_card[i][j]);
		fprintf(pfile, "\n");
	}

	fclose(pfile);
}


//發牌與牌面配置
void init_game_start_table_and_hand(int32_t *card, int32_t table[4][5], int32_t **hand_card, int32_t player_number){

	//隨機配置牌
	range_shuffle(card, 104);

	//發牌給每個人
	for (int32_t i = 0 ; i < 10; i++)
		for (int32_t j = 0 ; j < player_number; j++)
			hand_card[j][i] = card[(i * player_number + j)];

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

//輸出字串並接收一個數值
int32_t read_input(char *str){
	int32_t temp = 0 ;
	printf("--------------\n");
	printf("%s", str);
	printf("Choose: ");
	scanf("%d", &temp);
	return temp;
}


//choose 0 => new game
//choose 1 => load game
void start_a_game(int32_t choose){

	//new game
	if (choose == 0){
		//int32_t **hand_card_ptr = hand_card;
		hand_card = declared_two_pointer(player, 10);
		init_game_start_table_and_hand(card, table, hand_card, player);
		//free(hand_card_ptr);


		//設定電腦強度(丟到function pointer array內)
		set_agent_level();

	//load game
	}else if (choose == 1){
		//int32_t **hand_card_ptr = hand_card;
		hand_card = declared_two_pointer(10, 10);
		if (load_now_progress() == -1){
			start_a_game(0);
			return;
		}
		set_agent_level();

		fprintf(stderr, "\n\n讀取進度中");
		for (int32_t i = 0 ; i < 10 ; i++){
			usleep(350000);
			fprintf(stderr, ".");
		}

		fprintf(stderr, "\n< 已成功讀取進度 >\n");
		sleep(2);
		//free(hand_card_ptr);
	}

	//int32_t last[8] = {0};

	print_table_status(table, 4, 5);
	while (count_hand_card(hand_card[0]) != 0){
		CSIE_40771131H_determine_last_index_index(table, table_last_index , row_table_point);

		User_pick_and_choose_num = 0;
		int32_t record_card[10] = {0};
		int32_t player_list[10] = {0};

		//出牌階段
		printf("< new message >\n");
		for (int32_t i = 0 ; i < player; i++){
			int32_t choose_card = agent_pick[i](table, hand_card[i]);
			if (choose_card == -1){
				printf("< 排名概況 >\n");
				goto game_end;
			}

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
		getchar();
		getchar();
		system("clear");

		//系統判定牌放置階段
		User_pick_and_choose_num = 1;
		for (int32_t i = 0 ; i < player ; i++){
			system("clear");
			printf("【牌局戰況】\n");
			printf("< new message >\n");

			int32_t temp = put_one_card(table, player_points, player_list[i]+1, hand_card[player_list[i]], record_card[i]);
			if (temp == -1){
				//choose
				int32_t res_row = agent_choose[player_list[i]](table, record_card[i]);

				CSIE_40771131H_determine_last_index_index(table, table_last_index , row_table_point);
				printf("Player %d－－Pick row: %d, row points: %d, new title: %d\n", player_list[i]+1, res_row+1, row_table_point[res_row], record_card[i]);
				int32_t now_point = player_points[player_list[i]];
				pick_one_row(table, player_points, player_list[i]+1, res_row);
				put_one_card_and_clear_hand(hand_card[player_list[i]], record_card[i]);

				int32_t cur_point = player_points[player_list[i]];
				printf("now: point %d  ( + %d )\n", cur_point, cur_point - now_point);

				//important!!
				table[res_row][0] = record_card[i];

			}
			print_table_status(table, 4, 5);
			printf("Enter...\n");
			getchar();
		}
	}

	//Game over
	fprintf(stderr, "Game Over");
	for (int32_t i = 0 ; i < 10 ; i++){
		usleep(350000);
		fprintf(stderr, ".");
	}
	printf("\n\n");

	//list rank
game_end:
	system("clear");

	list_rank(player_points, set_points, player);
	printf("Enter...\n");
	getchar();
	getchar();
}

//設定電腦級別
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

//load progress
int32_t load_now_progress(){
	FILE *pfile = NULL;

	if ((pfile = fopen("40771131H_project_store.txt", "r")) ==NULL){
		perror("Error: ");
		return -1;
	}

	fscanf(pfile, "[player]%d\n", &player);
	fscanf(pfile, "[set_points]%d\n", &set_points);
	fscanf(pfile, "[meau_choose]%d\n", &meau_choose);
	fscanf(pfile, "[meau_store]%d\n", &meau_store);
	fscanf(pfile, "[start_game_choose]%d\n", &start_game_choose);
	fscanf(pfile, "[game_setting]%d\n", &game_setting);
	fscanf(pfile, "[sort_hand]%d\n", &sort_hand);
	fscanf(pfile, "[choose_hand_user]%d\n", &choose_hand_user);

	char temp[100000];

	fgets(temp, 99999, pfile);

	int32_t count = 0;
	for (int32_t i = 0 ; i < 20; i++){
		if (i != 0 && i%5==0) count+=1;
		fscanf(pfile, "%d", &table[count][i%5]);
	}
	fgets(temp, 99999, pfile);
	fgets(temp, 99999, pfile);
	for (int32_t i = 0 ; i < 10 ; i++)
		fscanf(pfile, "%d", &agent_level[i]);
	fgets(temp, 99999, pfile);


	fgets(temp, 99999, pfile);
	for (int32_t i = 0 ; i < 10 ; i++)
		fscanf(pfile, "%d", &player_points[i]);
	fgets(temp, 99999, pfile);

	fgets(temp, 99999, pfile);

	count = 0;
	for (int32_t i = 0 ; i < 10 * player ; i++){
		if (i != 0 && i%10==0){
			count+=1;
			fgetc(pfile);
		}
		int32_t tppp = 0;
		fscanf(pfile, "%d", &tppp);
		hand_card[count][i%10] = tppp;
	}

	fclose(pfile);
}


//開始遊戲
void start_setting_function(){
	start_game_choose = 0;
	init_all_val();
	agent_level[0] = 0;
	while (1){
		system("clear");
		print_meau_start_game();
		start_game_choose = read_input("輸入您的選項\n");
		if (start_game_choose == 1){
			game_setting = 0;
			while (1){
				system("clear");
				print_meau_game_setting();
				game_setting = read_input("輸入您的選項\n");

				//設定規則
				if (game_setting == 1){
					int32_t game_player_mode = 0;
					while (1){
						system("clear");
						printf("1) 普通玩法\n");
						printf("2) 變體規則\n");
						printf("3) 回上一頁\n");
						game_player_mode = read_input("輸入您的選項\n");

						if (game_player_mode == 1){
							system("clear");
							printf("< new message >\n");
							printf("已設定！\n");
							set_points = 172;
							printf("Enter...\n");
							getchar();
							getchar();

						}else if (game_player_mode ==2){
							system("clear");
							printf("(一般建議設定在15-30間)\n");
							printf("目前狂牛症標準: %d\n", set_points);
							int32_t set_point_temp = 0;
							while (1){
								printf("請輸入新的標準(1-171): ");
								scanf("%d", &set_point_temp);
								if (set_point_temp >= 1 && set_point_temp <= 171){
									set_points = set_point_temp;
									break;
								}else printf("Input error!\n");
							}
						}else if (game_player_mode ==3) break;
						else printf("Input error!\n");

					}

					//輸入遊戲人數
				}else if (game_setting == 2){
					system("clear");
					printf("目前遊戲人數: %d\n", player);
					int32_t player_temp = 0;
					while (1){
						printf("請輸入新的遊戲人數(2-10): ");
						scanf("%d", &player_temp);
						if (player_temp < 2 || player_temp > 10)
							printf("Input error!\n");
						else{
							player = player_temp;
							printf("已更改>>遊戲人數: %d\n\n", player);
							printf("Enter...");
							getchar();
							getchar();
							break;
						}
					}
				}else if (game_setting == 3){
					int32_t agent_set_level_choose = 0;
					while (1){
						system("clear");
						printf("0) 玩家參賽: ");
						if (agent_level[0] == 0) printf("Yes\n");
						else printf("No\n");

						for (int32_t i = 1; i < player; i++){
							printf("%d) Agent level: %d\n", i, agent_level[i]);
						}
						printf("%d) 回上一頁\n", player);

						agent_set_level_choose = read_input("請輸入想更動的編號\n");
						if (agent_set_level_choose == player) break;
						else if (agent_set_level_choose == 0){
							if (agent_level[0] == 0){
								printf("已預設第一位電腦等級為3\n");
								agent_level[0] = 3;
							}else {
								agent_level[0] = 0;
								printf("已完成！\n");
							}
							printf("Enter...\n");
							getchar();
							getchar();
						}else if (agent_set_level_choose < 0 || agent_set_level_choose > player){
							printf("Input error!\n");
						}else{
							int32_t temp_level = 0;
							printf("\n\n>>>該電腦目前的等級為: %d\n", agent_level[agent_set_level_choose]);
							while (1){
								printf("在普通局內，等級3最強，等級1最弱\n");
								printf("在狂牛局內，等級3, 1最強，等級2最弱(狂牛標準正常的情況下)\n");
								temp_level = read_input("請輸入等級(1-3)\n");
								if (temp_level < 1 || temp_level > 3) printf("Input error!\n");
								else{
									agent_level[agent_set_level_choose] = temp_level;
									break;
								}
							}
						}
					}


				}else if (game_setting == 4){
					start_a_game(0);
					if (meau_store == 2){
						printf("< 此為暫時戰況 >\n");
						return;
					}

					break;
				}else if (game_setting == 5) break;
				else printf("Input error!\n");
			}


		}else if (start_game_choose == 2){
			start_a_game(1);
			if (meau_store == 2){
				printf("< 此為暫時戰況 >\n");
				return;
			}
		}else if (start_game_choose == 3){
			printf("~結束遊戲~\n");
			return;
		}else printf("Input error!\n");
	}
}

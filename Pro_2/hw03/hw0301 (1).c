#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

//複製字串
void cp_str(char *str, char *sor){ int32_t count = 0;
	while (1){
		if (*(sor+count) =='\0'){
			*(str+count) = '\0';
			return;
		}
		*(str+count) = *(sor+count);
		count+=1;
	}
}

//取得一列有幾個欄位
int32_t row_num(char *str, FILE *pfile){
	int32_t count = 0, comment = 1;
	while (1){
		fscanf(pfile, "%c", str+count);
		if (feof(pfile)) return comment;
		if (*(str+count)== '\n' || *(str+count) == EOF){
			*(str+count) = '\0';
			return comment;
		}else if (*(str+count) == ',') comment+=1;
		count+=1;
	}
	return comment;
}

//取得csv檔中，最多行的列其行總數為何
int32_t get_max_len(char *str, FILE *pfile){
	int32_t max = row_num(str, pfile);
	while (!feof(pfile)){
		int32_t tp = row_num(str, pfile);
		if (tp > max) max = tp;
	}
	fseek(pfile, 0L, SEEK_SET);

	return max;
}

//一列中，客隊、主場跟其勝負結果
//並且取得這3個的索引值在哪（有可能不固定位置)
typedef struct Row{
	char hometeam[100];
	char awayteam[100];
	char ftr;
	int32_t home_index;
	int32_t away_index;
	int32_t ftr_index;
}S_row;


//每隊的勝負、平手、分數和排名狀況
typedef struct Team{
	char name[500];
	int32_t win;
	int32_t lose;
	int32_t draw;
	int32_t points;
	int32_t position;
}S_team;


//把換行符號取代掉
void modify_line(char *str){
	int32_t count = 0;
	while (*(str+count) !='\0'){
		if (*(str+count) == '\n'){
			*(str+count) = '\0';
			return;
		}
		count +=1;
	}
}

//排序排名
void bubble_struct(S_team tp[], int32_t size){
	S_team temp;
	for (int32_t i = 0 ; i < size; i++){
		for (int32_t j = 1 ; j < size-i; j ++){
			if (tp[j].points > tp[j-1].points){
				temp = tp[j];
				tp[j] = tp[j-1];
				tp[j-1] = temp;
			}
		}
	}
}

//讀每個逗號之間的文字進去tp_str內
//讀到尾巴回傳0，還可以讀回傳1
int32_t save_char(char *tp_str, char *str){
	static int32_t count = 0;
	int32_t num = 0;
	while (1){
		if (*(str+count) == '\0'){
			*(tp_str+num) = '\0';
			count = 0;
			return 0; 
		}else if (*(str+count) !=','){
			*(tp_str+num) = *(str+count);
			num+=1;
		}else{
			*(tp_str+num) = '\0';
			count+=1;
			return 1;
		}
		count+=1;
	}
}


//找指定名稱在隊伍名單中哪個位置，不存在回傳-1
int32_t find_name(S_team tp[], int32_t size, char *str){
	for (int32_t i = 0;  i < size; i++){
		if (strcmp(tp[i].name, str) == 0) return i;
	}
	return -1;
}

int main(){

	S_team team[10005];
	S_row tp_row;

	FILE *pfile = NULL;
	char *str = calloc(100005, sizeof(char));
	char *filename = calloc(201, sizeof(char));

	printf("Please enter the season data file: ");
	fgets(filename, 200, stdin);
	modify_line(filename);

	//檢查檔案可不可開啟
	if ((pfile = fopen(filename, "r"))==NULL){
		printf("The file don't be opened!\n");
		perror("Error: ");
		return 0;
	}

	//取得行最長的長度
	int32_t max = get_max_len(str, pfile);
	
	char *tp_str = calloc(501, sizeof(char));

	tp_row.home_index = -1;
	tp_row.away_index= -1;
	tp_row.ftr_index= -1;

	//紀錄FTR, HOMETEAM, AWAYTEAM位置
	row_num(str, pfile);
	int32_t index = 0;
	while (1){
		int32_t tpp = save_char(tp_str, str);
		if (strcmp(tp_str, "HomeTeam") == 0) 
			tp_row.home_index = index;
		else if (strcmp(tp_str, "AwayTeam") == 0) 
			tp_row.away_index = index;
		else if (strcmp(tp_str, "FTR") == 0)
			tp_row.ftr_index = index;
		
		if (tpp == 0) break;
		index +=1;
	}

	if (tp_row.home_index == -1) printf("Your data haven't hometeam!\n");
	else if (tp_row.away_index ==-1) printf("Your data haven't awayteam!\n");
	else if (tp_row.ftr_index ==-1) printf("Your data haven't FTR!\n");
	
	if (tp_row.home_index==-1 ||tp_row.away_index == -1 ||tp_row.ftr_index==-1){
		printf("Please enter a correct data!\n");
		return 0;
	}

	//開始讀後面所有資料
	int32_t row_index = 0;
	while (!feof(pfile)){
		index = 0;
		int32_t rowlen = row_num(str, pfile);
		char *hometeam = calloc(501, sizeof(char));
		char *awayteam = calloc(501, sizeof(char));
		char ftr;

		while (1){
			int32_t tpp;
			if (index == tp_row.home_index)
				save_char(hometeam, str);
			else if (index == tp_row.away_index)
				save_char(awayteam, str);
			else if (index == tp_row.ftr_index){
				save_char(tp_str, str);
				ftr = *tp_str;
			}else{
				tpp = save_char(tp_str, str);
				if (tpp ==0) break;
			}
			index+=1;
		}

		int32_t hometemp = find_name(team, row_index, hometeam);
		int32_t awaytemp = find_name(team, row_index, awayteam);

		if (hometemp == -1){
			cp_str(team[row_index].name, hometeam);
			hometemp = row_index;
			row_index+=1;
		}
		if (awaytemp == -1){
			cp_str(team[row_index].name, awayteam);
			awaytemp = row_index;
			row_index+=1;
		}

		if (ftr == 'H'){
			team[hometemp].win +=1;
			team[awaytemp].lose +=1;
		}else if (ftr == 'A'){
			team[awaytemp].win +=1;
			team[hometemp].lose +=1;
		}else if (ftr =='D'){
			team[awaytemp].draw +=1;
			team[hometemp].draw +=1;
		}else{
			printf("Your data error! (FTR is 'A' or 'D' or 'H')\n");
			printf("Please enter a correct data!\n");
			return 0;
		}
	}
	for (int32_t i = 0 ; i < row_index ; i++)
		team[i].points = team[i].win *3 + team[i].draw;


	bubble_struct(team, row_index);

	//排名各隊，若分數相同則名次相同的處理
	team[0].position = 1;
	int32_t position_temp = 1;
	for (int32_t i = 1 ; i < row_index ; i++){
		if (team[i].points == team[i-1].points){
			team[i].position = position_temp;
		}else{
			team[i].position = i+1;
			position_temp = i+1;
		}
	}

	//讓使用者輸入隊伍名稱
	char *inputeam = calloc(501, sizeof(char));
	printf("Please enter Team Name: ");
	fgets(inputeam, 500, stdin);
	modify_line(inputeam);

	//輸出查詢結果
	int32_t output = find_name(team, row_index, inputeam);
	if (output ==-1) printf("No such a team!\n");
	else{
		printf("Points:\t\t%d\n", team[output].points);
		printf("Win:\t\t%d\n", team[output].win);
		printf("Draw:\t\t%d\n", team[output].draw);
		printf("Lose:\t\t%d\n", team[output].lose);
		printf("Position:\t%d", team[output].position);
		int32_t teamposition = team[output].position;
		
		if (teamposition >= 10 && teamposition <=20) printf("th\n");
		else if (teamposition % 10 == 1) printf("st\n");
		else if (teamposition % 10 == 2) printf("nd\n");
		else if (teamposition % 10 == 3) printf("rd\n");
		else printf("th\n");
	}

	fclose(pfile);
	return 0;
}

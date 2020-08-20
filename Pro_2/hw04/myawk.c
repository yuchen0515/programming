#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

//複製字串
void cpstr(char *str, char *sor){
	int32_t count = 0;
	while (1){
		if (*(sor+count) == '\0'){
			str = realloc(str, count);
			*(str+count) = '\0'; return;
		}else *(str+count) = *(sor+count);
		count +=1;
	}
}

//檢查 $+數字的pattern
int32_t match_pattern(char *str){
	int32_t count = 0;
	while (1){
		if (*(str+count) == '\0') return 1;
		if (count == 0 && *(str) != '$') return 0;
		if (count > 0 && !(*(str+count) >= '0' && *(str+count) <='9')) return 0;
		count +=1;
	}
}

int main(int argc, char *argv[]){
    int32_t c = 0, record_F = 0;
	int32_t getop_count = 0, check_count = 0;
	char *str = calloc(1000, sizeof(char));
	char *spp = calloc(1000, sizeof(char));

	spp[0] = ' '; spp[1] = '\0';

	//輸入太少肯定輸入錯了
	if (argc < 4 || argc > 7){
		printf("Your input error!\n");
		return 0;
	}
    
	//檢查-F和參數
	if (argv[1][0] == '-'){
		while ((c = getopt( 3, argv, "F:")) != -1){
			switch( c ){
				case 'F':
					if (strcmp(optarg, argv[2])!=0)
						getop_count +=1;
					record_F = 1;
					cpstr(str, optarg);
					break;
				default:
					printf( "Your option isn't as \"F\"\n"); 
					return 0;
			}
			check_count +=1;
		}
	}

	//例外處理，不符合條件的都提示使用者並結束
	int32_t determine = argc + getop_count;
	if (record_F == 1 && strlen(str) != 1){
		printf("You can only to set \"one\" character\n");
		return 0;
	}

	if ((record_F ==1 && determine != 7) && (record_F == 0 && determine != 5)){
		printf("Input error!\n");
		return 0;
	}


	//檢查檔案是否可開啟
	FILE *pfile = NULL;
	if ((pfile = fopen(argv[argc-1], "r")) == NULL){
		printf("Your file don't be opened!\n");
		perror("Error: ");
		return 0;
	}
	if (record_F == 1) cpstr(spp, str);

	//檢查'$+數字'的格式是否正確
	if (match_pattern(argv[argc-2])==0 || match_pattern(argv[argc-4])==0){
		printf("Your argument should be \"$\" + \"integer\".\n");
		return 0;
	}

	//讀取使用者想取得的位置
	int32_t o_l = 0, t_l = 0;
	sscanf(argv[argc-2], "$%d", &t_l);
	sscanf(argv[argc-4], "$%d", &o_l);

	char *spt = calloc(100001, sizeof(char)), *token;
	char *copy = calloc(100001, sizeof(char));

	//開始讀檔
	while (!feof(pfile)){
		fgets(spt, 100000,pfile);
		cpstr(copy, spt);

		if (feof(pfile)) break;

		int32_t cou = 1;

		//字元分割
		token = strtok(spt, spp);
		while (token != NULL){
			if (cou == o_l) printf("%s", token);
			token = strtok(NULL, spp);
			cou +=1;
		}
		printf("%s", argv[argc-3]);

		//因有先後順序之分，因此重複兩次
		cou = 1;
		token = strtok(copy, spp);
		while (token != NULL){
			if (cou == t_l) printf("%s", token);
			token = strtok(NULL, spp);
			cou +=1;
		}

		printf("\n");
	}

	fclose(pfile);

	return 0;
}

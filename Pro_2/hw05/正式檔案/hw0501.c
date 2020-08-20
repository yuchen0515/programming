#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h> 

//把字串換行刪掉
void modify(char *str){
	int32_t count = 0 ;
	while (1){
		if (*(str+count) == '\n' ||*(str+count) == '\0'){
			*(str+count) = '\0';
			return ;
		}
		count+=1;
	}
}

//encode
void base_64_pt(uint32_t pt, uint32_t equ, FILE *pfile){
	static int32_t tpp = 1;
	char *str = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	int32_t count = 18;
	equ = (equ << (32-(count+6))) >> (32-(count+6));
	while (count >= 0){
		pt = pt << (32-(count+6)) >> (32-(count+6));
		uint32_t chr = pt >> count;
		if (pt==0 || equ ==0){
			if (count == 18) return;
			fwrite("=", 1, sizeof(char), pfile);
		}else{
			fwrite((str+chr), 1, sizeof(char), pfile);
		}
		if (!(equ ==0 && count ==0) && tpp % 76 == 0) 
			fwrite("\n", 1, sizeof(char), pfile);
		count -= 6;
		tpp+=1;
		equ >>= 6;
	}
}

//decode
void base_64_decode(uint32_t pt, FILE *pfile, char *name, char *name2){
	static int32_t tpp = 1;
	char strr[25555];
	strcat(strr, "ba");
	char *str = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	int32_t count = 16;

	//讀入24bits, 每次取 6bits取出數字後，再組裝起來
	while (count >= 0){
		count = -1;
		pt = pt << (32-(count+8)) >> (32-(count+8));
		uint32_t chr = pt >> count;
		
		char *find = strchr(str, (char)chr);
		uint32_t tppp = find - str;
		if (find != NULL){
			fwrite(&tppp, 1, sizeof(uint8_t), pfile);
		}

		count -= 8;
	}
	strcat(strr, "se64 -d ");
	strcat(strr, name2);
	strcat(strr, ">");
	strcat(strr, name);
	popen(strr, "r");
	
}

//定義option, enc=>e, dec=>d, output=>o
struct option long_options[] = {  
	{ "enc",  0, NULL, 'e' },  
	{ "dec", 0, NULL, 'd' },  
	{ "output", 0, NULL, 'o' },  
	{  0, 0, 0, 0},  
};  

int main(int argc, char *argv[]){

	int32_t c = 0, index = 0;
	int32_t record_e = 0, record_d = 0, record_o = 0;
	int32_t cou = 0;
	int32_t pos_e = 0 , pos_o = 0, pos_d = 0;

	//處理參數
	while ((c = getopt_long(argc, argv, "edo", long_options, &index)) != -1 ){
		switch( c ){
			case 'e':
				record_e += 1;
				pos_e = cou +1;
				cou+=1;
				break;
			case 'd':
				record_d += 1;
				pos_d = cou +1;
				cou+=1;
				break;
			case 'o':
				record_o += 1;
				pos_o = cou +1;
				cou+=1;
				break;
			default:
				printf("Your argument input error!\n");
				printf("You should refer README.pdf!\n");
				return 0;
		}
		cou +=1;
	}

	//取得位置
	//用argv取得

	if (argc != 5){
		printf("You should input four argument and refer README.pdf!\n");
		return 0;
	}

	if (record_e ^ record_d != 1){
		printf("The encode and decode argument, you should choice \"one\"\n");
		printf("You should refer README.pdf!\n");
		return 0;
	}

	if (record_e > 1 || record_d > 1 || record_o >1){
		printf("You input some argument as same!\n");
		printf("You should refer README.pdf!\n");
		return 0;
	}


	FILE *pfile = NULL, *pfile2 = NULL;
	char *str = calloc(5000, sizeof(char));
	char *str2 = calloc(5000, sizeof(char));


	if (pos_e > pos_o || pos_d > pos_o){
		pfile = fopen(argv[4], "r");
		pfile2 = fopen(argv[3], "w");
		strcpy(str, argv[3]);
		strcpy(str2, argv[4]);
	}else{
		pfile = fopen(argv[3], "r");
		pfile2 = fopen(argv[4], "w");
		strcpy(str, argv[4]);
		strcpy(str2, argv[3]);
	}

	if ((pfile = fopen(str2, "r")) ==NULL){
		perror("Error: ");
		return 0;
	}

	if ((pfile2 = fopen(str, "w")) ==NULL){
		perror("Error: ");
		return 0;

	}


	uint32_t count = 1, save = 0, red = 0;

	//encode
	if  (record_e >= 1){
		while (1){
			uint8_t tp = 0;
			fread(&tp, 1, sizeof(uint8_t), pfile);
			if ((feof(pfile))){
				red <<= (8 * (3- (count%3)+1));
				save <<= (8 * (3- (count%3)+1));
				base_64_pt(save, red, pfile2);
				fwrite("\n", 1, sizeof(char), pfile);

				break;
			}
			red = (red<<8) + 255;
			save = (save << 8) | tp;

			if (count%3 ==0){
				base_64_pt(save, red, pfile2);
				save = 0;
				red = 0;
			}
			count +=1;
		}
	}else if (record_d >= 1){
		char *str3 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
		base_64_decode(save, pfile2, str, str2);

		while (1){
			uint8_t tp = 0;
			fseek(pfile, 0L, SEEK_END);
			break;

			if (feof(pfile)){
				break;
			}
			fread(&tp, 1, sizeof(char), pfile);

			if (tp=='\n') continue;
			char *find = strchr(str3, tp);
			if (find != NULL){
				uint32_t tep = (char*)(find) - str3;
				//printf("%d\n", tep);
				fwrite(&tep, 1, sizeof(uint8_t), pfile2);
			}
			save = (save << 8) | tp;

			if (count % 3 == 0){
				base_64_decode(save, pfile2, str, str2);
				save = 0;
			}

			count+=1;
		}
	}

	free(str);
	free(str2);

	return 0;
}

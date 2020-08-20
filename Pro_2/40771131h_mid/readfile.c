#include "readfile.h"


void catstr(char str[], char pt[]){

	int32_t str_len = strlen(str);
	int32_t pt_len = strlen(pt);
	int32_t i = 0;
	str = realloc(str, str_len + pt_len);

	for (i = str_len; i < str_len + pt_len; i++){
		*(str + i) = *(pt + i-str_len);
	}
	*(str + i) = '\0';
}

int32_t mark(char c, char pattern){
	if (c==pattern || pattern =='?') return 1;
	return 0;
}

//驗證輸入是否符合樣式
int32_t pat_verify(char text[], char pat[]){
	int32_t tind = 0, pind = 0;
	int32_t aind = -1;
	while (tind < strlen(text)){
		int32_t end = pind == strlen(pat);
		if (!(end) && mark(text[tind], pat[pind])){
			tind+=1;
			pind+=1;
		}else if (!(end) && pat[pind] == '*'){
			aind = pind;
			pind +=1;
		}else if (aind != -1){
			pind = aind + 1;
			tind +=1;
			continue;
		}else return 0;
	}
	while ((pind < strlen(pat)) && (pat[pind] == '*')) pind+=1;
	return pind == strlen(pat);
}

//將str字串的所有space除掉
void del_space(char *str){

	int32_t leng = strlen(str), i = 0;
	int32_t count = 0, ac_count = 0;
	char num[leng];

	while (*(str+count) !='\0'){
		if (*(str+count) != ' '){
			*(num+ac_count) = *(str+count);
			ac_count+=1;
		}
		count +=1;
	}

	for (i = 0 ; i < ac_count; i++) *(str+i) = *(num+i);
	*(str+i) = '\0';
}

//仿fgets，若str大小不足，自動擴展str長度
char* readget(char *str, int32_t size, FILE* stream, int32_t choice){
	int32_t result_size = size, count = 0;
	char s = fgetc(stream);

	//if (s==EOF || s=='\n') return NULL;
	if (s==EOF) return NULL;

	while ( s != '\n' && s != EOF){
		*(str+count) = s;
		if (count+1 == result_size){
			result_size+=1;
			str = realloc(str, result_size);
		}
		count+=1;
		s = fgetc(stream);
	}
	*(str+count) = '\0';
	if (choice == 1) del_space(str);

	return str;
}

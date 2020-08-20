#include "readfile.h"

int32_t isalpha_(char p);
int32_t iskeyword(char *str);
void ptcolor(char *str);

int main(){

	FILE *pfile = NULL;
	char *str = calloc(999,sizeof(char));

	printf("Please input a file name: ");
	readget(str, 2, stdin, 0);
	if ((pfile = fopen(str, "r")) == NULL){
		printf("The don't be open!\n");
		perror("Error: ");
		return 0;
	}

	while (!(feof(pfile))){
		readget(str, 10000, pfile, 0);
		if (feof(pfile)) break;
		char ptstr[999999];
		int32_t count = 0;
		int32_t ind = 0;
		while (1){
			if ((*(str+count) =='\0')){
				*(ptstr+ind) = '\0';
				ptcolor(ptstr);
				printf("\n");
				break;
			}else if (*(str+count)=='/' && *(str+count+1)=='/'){
				*(ptstr+ind) = '\0';
				ptcolor(ptstr);
				printf("\x1b[;95;1m%s\n\x1b[0;m", (str+count));
				break;
			}else if ((isalpha_(*(str+count))==0)){
				*(ptstr+ind) = '\0';
				ptcolor(ptstr);
				if ((*(str+count) == '[') || (*(str+count) ==']') || (*(str+count) == '(') || (*(str+count) == ')') || (*(str+count) == '{') || (*(str+count) == '}')){
					printf("\x1b[;37;33m%c\x1b[0;m", *(str+count));
				}else{
					printf("%c", *(str+count));
				}
				ind = 0;
			}else{
				*(ptstr+ind) = *(str+count);
				ind+=1;
			}
			count +=1;
		}
	}
	fclose(pfile);

	return 0;
}


//check alpha and _
int32_t isalpha_(char p){
	if ((p >= 'a') && (p <='z')) return 1;
	if ((p >= 'A') && (p <='Z')) return 1;
	if (p == '_') return 1;
	if (p >='0' && p <='9') return 1;
	return 0;
}

//return 1 ==> orange
//return 2 ==> blue
//return 0 ==> no
int32_t iskeyword(char *str){
	if (strcmp(str, "break") == 0) return 1;
	if (strcmp(str, "case") == 0) return 1;
	if (strcmp(str, "continue") == 0) return 1;
	if (strcmp(str, "default") == 0) return 1;
	if (strcmp(str, "do") == 0) return 1;
	if (strcmp(str, "else") == 0) return 1;
	if (strcmp(str, "for") == 0) return 1;
	if (strcmp(str, "goto") == 0) return 1;
	if (strcmp(str, "if") == 0) return 1;
	if (strcmp(str, "return") == 0) return 1;
	if (strcmp(str, "sizeof") == 0) return 1;
	if (strcmp(str, "switch") == 0) return 1;
	if (strcmp(str, "while") == 0) return 1;
	if (strcmp(str, "char") == 0) return 2;
	if (strcmp(str, "const") == 0) return 2;
	if (strcmp(str, "double") == 0) return 2;
	if (strcmp(str, "enum") == 0) return 2;
	if (strcmp(str, "extern") == 0) return 2;
	if (strcmp(str, "float") == 0) return 2;
	if (strcmp(str, "int8_t") == 0) return 2;
	if (strcmp(str, "int16_t") == 0) return 2;
	if (strcmp(str, "int32_t") == 0) return 2;
	if (strcmp(str, "int64_t") == 0) return 2;
	if (strcmp(str, "typedef") == 0) return 2;
	if (strcmp(str, "uint8_t") == 0) return 2;
	if (strcmp(str, "uint16_t") == 0) return 2;
	if (strcmp(str, "uint32_t") == 0) return 2;
	if (strcmp(str, "uint64_t") == 0) return 2;
	if (strcmp(str, "long") == 0) return 2;
	if (strcmp(str, "short") == 0) return 2;
	if (strcmp(str, "signed") == 0) return 2;
	if (strcmp(str, "static") == 0) return 2;
	if (strcmp(str, "struct") == 0) return 2;
	if (strcmp(str, "union") == 0) return 2;
	if (strcmp(str, "unsigned") == 0) return 2;
	if (strcmp(str, "void") == 0) return 2;
	if (strcmp(str, "int") == 0) return 2;
	return 0;
}
void ptcolor(char *str){
	int32_t temp = iskeyword(str);
	if (temp == 1){
		printf("\x1b[;93;1m%s\x1b[0;m", str);
	}else if (temp ==2){
		printf("\x1b[;94;1m%s\x1b[0;m", str);
	}else printf("%s", str);
}

#include "readfile.h"

//檢驗是否為字母，若選擇為1順便將其平移到0-25
int32_t alpha(char *str, int32_t choice){
	if (*str >= 'a' && *str <= 'z'){
		if (choice == 1) *str = *str - 'a';
		return 1;
	}else if (*str >= 'A' && *str <= 'Z'){
		if (choice == 1) *str = *str - 'A';
		return 2;
	}else return 0;
}

//掃描檔案 (key_file)，格式不符回傳為-1或-2
int32_t scan_key(FILE *file, int32_t enc[], int32_t dec[]){

	char *str = calloc(10, sizeof(char));
	int32_t *check1 = calloc(26, sizeof(int32_t)), *check2 = calloc(26, sizeof(int32_t));
	 
	while ((readget(str, sizeof(str), file, 1) !=NULL)){

		if (strlen(str) != 3) return -1; 
		if (alpha((str+0), 1)== 0) return -1;
		if (*(str+1) != ':') return -1;
		if (alpha((str+2), 1)== 0) return -1;
		
		if ((check1[*(str+0)] == 0) && (check2[*(str+2)] ==0)){
			enc[*(str+0)] = *(str+2);
			dec[*(str+2)] = *(str+0);
			check1[*(str+0)] = 1;
			check2[*(str+2)] = 1;
		}else return -2;

	}

	return 1;
}

int main(){

	int32_t enc[26], dec[26];
	char *input_name = calloc(2, sizeof(char)), *output_name = calloc(2, sizeof(char));
	char *key_name = calloc(2, sizeof(char)), *choice = calloc(2, sizeof(char)), p;
	FILE *input = NULL, *output = NULL, *key = NULL;

	for (int32_t i = 0; i < 26; i++){
		enc[i] = -1;
		dec[i] = -1;
	}

	//開input檔，看有沒有問題
	printf("Please enter the input key: ");
	readget(input_name, 2, stdin, 0);
	if ((input = fopen(input_name, "r")) == NULL){
		printf("Input file don't be open!\n");
		perror("Error: ");
		return 0;
	}

	//開output檔，看有沒有問題
	printf("Please enter the output key: ");
	readget(output_name, 2, stdin, 0);
	if ((output = fopen(output_name, "w")) == NULL){
		printf("Output file don't be open!\n");
		perror("Error: ");
		return 0;
	}

	//讀key檔，看看格式有沒有問題
	printf("Please enter the key file: ");
	readget(key_name , 2, stdin, 0);
	if ((key = fopen(key_name, "r")) == NULL){
		printf("Key file don't be open!\n");
		perror("Error: ");
		return 0;
	}
	int32_t tp = scan_key(key, enc, dec);
	if (tp == -2){
		printf("你的Key file，對應字母不唯一，請重新檢查！\n"); 
		return 0;
	}else if (tp == -1){
		printf("你的Key file輸入格式有問題，請重新確認！\n");
		return 0;
	}
	fclose(key);

	//檢查使用者的選擇，輸入是否不符格式，不符則提示使用者重新輸入
	int32_t check_choice = 0;
	while (check_choice == 0){
		printf("Encryption (1) or Decryption (2): ");
		readget(choice , 2, stdin, 0);
		if (strlen(choice) != 1) printf("Your input too long!\n");
		else if (*(choice) =='1' || *(choice) =='2'){
			check_choice = 1;
		}else{
			printf("Input error!\n");
			printf("You should input 1[enc] or 2[dec]\n");
		}
	}

	//讀取input並根據key轉換輸出到output
	while (!(feof(input))){
		if ((p = fgetc(input)) ==EOF) break;
		int32_t tp = alpha(&p, 1), add = (tp==1) ? 'a' : 'A';

		if (tp==0) fprintf(output, "%c", p);
		else if (*choice =='1' && enc[p] !=-1)
			fprintf(output, "%c", enc[p]+add);
		else if (*choice =='2' && dec[p] !=-1)
			fprintf(output, "%c", dec[p]+add);
		else fprintf(output, "%c", p);
	}
	fclose(input);
	fclose(output);

	printf("Done!\n");

	return 0;
}

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void modify(char *str){
	int32_t count = 0;
	while (1){
		if (*(str+count) =='\n' || *(str+count) =='\0'){
			*(str+count) = '\0';
			return;
		}
		count+=1;
	}
}

void tran(uint32_t save[], int32_t *index){
	uint32_t temp = 0;
	uint32_t tp = 0;
	scanf("%u", &temp);
	scanf("%u", &tp);
	temp += tp <<8;

	save[*index] = temp;
	*index+=1;
}

void dump(FILE *pfile, FILE *pfile2, uint32_t save[], char *str){
	int64_t start = ftell(pfile);
	uint64_t count = 0;
	uint32_t temp = 0;
	int32_t reg = 0;
	uint64_t save2[10];
	while (1){
		int64_t address = ftell(pfile);
		int32_t check = 0;
		fread(&temp, 1, sizeof(uint16_t), pfile);
		if (feof(pfile)){
			if (reg ==2){
				printf("Done!\n");
				for (int32_t i = 0 ; i < reg; i++){
					printf("%lu ", save2[i]);
					fprintf(pfile2, "%lu ", save2[i]);
				}
				printf("%s\n", str);
				fprintf(pfile2, "%s\n", str);
			}else{
				printf("not found ! %s\n", str);
				fprintf(pfile2, "not found ! %s\n", str);
			}
			fseek(pfile, 0L, SEEK_SET);
			return;
		}
		if (temp == save[0]){
			check = 1;
			for (int32_t i = 1 ; i < 4 ; i++){
				fread(&temp, 1, sizeof(uint16_t), pfile);
				if (temp != save[i]){
					check = 0;
					break;
				}
			}
			if (check == 0){
				fseek(pfile, address+2, SEEK_SET);
			}
		}
		count = address - start;
		
		if (check){
			save2[reg] = count -4;
			reg+=1;
		}

	}

}

int main(){

	FILE *pfile = NULL;
	FILE *pfile2 = NULL;

	if ((pfile = fopen("G4XUSR02.DAT", "rb")) ==NULL){
		printf("The file don't be opened!\n");
		perror("Error: ");
		return 0;
	}
	if ((pfile2 = fopen("hw0304_data.txt", "a")) ==NULL){
		printf("The file don't be opened!\n");
		perror("Error: ");
		return 0;
	}

	uint32_t save[4] = {0};
	while (1){
		int32_t index = 0;
		char *name = calloc(501, sizeof(char));
		printf("持續輸入？(0, 1): ");
		int32_t num = 0;
		scanf("%d", &num);
		if (num==0) break;

		printf("請輸入八維的數值: ");
		
		for (int32_t i = 0 ; i < 4 ; i++){
			tran(save, &index);
		}

		getchar();
		printf("請輸入角色名字: ");
		fgets(name, 500, stdin);
		modify(name);

		dump(pfile, pfile2, save, name);

		puts("");
	}



	fclose(pfile);
	fclose(pfile2);

	return 0;
}

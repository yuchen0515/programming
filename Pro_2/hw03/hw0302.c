#include "readfile.h"

//印出整條陣列，從0印到index項
void hexprint(uint64_t tp[], int32_t index){
	for (int32_t i = 0 ; i < index; i++){
		if (i==0) printf("%07lx ", tp[0]);
		else if (i == index-1)  printf("%04lx\n", tp[i]);
		else printf("%04lx ", tp[i]);
	}
}


int main(){
	FILE *pfile = NULL;
	char *name = calloc(2, sizeof(char));

	//和使用者要檔案名稱
	printf("Please enter the file: ");
	readget(name, 2, stdin, 1);

	//檔案開不起來提醒他
	if ((pfile = fopen(name, "r"))==NULL){
		printf("The file don't be opened!\n");
		perror("Error: ");
		return 0; 
	}

	uint64_t count = 0, save = 0, address = 0, temp = 0;
	uint64_t *savenum = calloc(9, sizeof(uint64_t));
	int32_t i = 0, check = 0, check2 = 1;

	//開始讀整個檔案
	while (!feof(pfile)){

		savenum[0] = count, check = 1;

		//一次讀16個字元，若無法讀就跳出
		for (i = 0; i < 16; i++){
			fread(&temp, 1, sizeof(char), pfile);

			//偶數就存後面，奇數存前面
			if (i&1){
				save += (temp<<8);
				if (savenum[(i>>1)+1] != save) check = 0;  //檢查是否上下行相等
				savenum[(i>>1)+1] = save;
			}else save = temp;

			//EOF時根據奇數、偶數給予最後一位數值並跳出
			if (feof(pfile)){
				if (i & 1) savenum[(i>>1)+1] = temp;
				else savenum[(i>>1)+1] = save;
				break;
			}

			count +=1;
		}

		//上下行相等，且近期第一次出現，印出一個*
		if (check && check2){
			printf("*\n");
			check2 = 0;
		}else if (check ==0){
			hexprint(savenum, (i>>1)+1+(i&1));
			check2 = 1;
		}
		//都沒執行以上的條件，代表連續好幾行相等

	}
	//印出最後位址
	printf("%07lx\n", count);

	fclose(pfile);

	return 0;
}

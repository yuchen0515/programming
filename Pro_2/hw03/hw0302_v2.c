//******, skip , odd
#include "readfile.h"

void initial(int64_t tp[], int32_t size){
	for (int32_t i = 0 ; i < size; i++){
		tp[i] = 0;
	}
}

void print_hex(int64_t tp[], int32_t index){
	for (int32_t i = 0 ; i < index; i++){
		if (i==0) printf("%07lx ", tp[0]);
		else printf("%04lx ", tp[i]);
	}
	printf("\n");
}

int main(){

	FILE *pfile = NULL;
	char *name = calloc(2,sizeof(char));
	printf("Please enter a file name: ");
	readget(name, 2, stdin, 0);

	if ((pfile = fopen(name, "r"))==NULL){
		printf("The file don't be opened!\n");
		perror("Error: ");
		return 0;
	}

	int64_t index = 0, count = 0, save = 0;
	int64_t savenum[9]= {0};
	int32_t check = 0;
	char temp = 0, tp = 0;

	while (!(feof(pfile))){
		initial(savenum, 9);
		count = 0, check = 1;
		if (feof(pfile)) break;
		savenum[0] = index;
		//printf("%07lx ", index);
		while (1){
			fscanf(pfile,"%c",&temp);

			if (temp == EOF) break;
			int64_t ab = (count+1)%16;
			if ((ab/2)==0) ab = 8;
			else ab= ab/2;
			if (count %2 ==0){
				save = (int64_t)temp;
			}else{ 
				save += (int64_t)temp << 8;

				if (save != savenum[ab]) check = 0;
				
				if ((count+1) % 16 !=0 && !(feof(pfile))){
					savenum[ab] = save;
					//printf("%04lx ", save);
				}
			}
			index+=1;
			if ((count+1) % 16 ==0 || feof(pfile)){
				if (save != 0x000a){
					//printf("%04lx\n", save);
					savenum[8] = save;
					if (check == 1) printf("*\n");
					else print_hex(savenum, ab);
				}else{
					index -=1;
					//printf("\n");
				}
				break;
			}
			count+=1;
		}
	}
	printf("%07lx\n", index);

	fclose(pfile);

	return 0;
}

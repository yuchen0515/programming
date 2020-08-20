#include <stdio.h>
#include <stdint.h>
#include "readfile.h"

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

	int64_t index = 0;
	int64_t count = 0;
	int64_t save = 0;
	char temp = 0;
	char tp = 0;
	int32_t check = 0;
	while (!(feof(pfile))){
		count = 0;
		if (feof(pfile)) break;
		printf("%07lx ", index);
		while (1){
			fscanf(pfile,"%c",&temp);

			if (temp == EOF) break;
			if (count %2 ==0){
				save = (int64_t)temp;
			}else{ 
				save += (int64_t)temp << 8;
				if ((count+1) % 16 !=0 && !(feof(pfile)))
					printf("%04lx ", save);
			}
			index+=1;
			if ((count+1) % 16 ==0 || feof(pfile)){
				if (save != 0x000a)
					printf("%04lx\n", save);
				else{
					index -=1;
					puts("");
				}
				break;
			}
			count+=1;
		}
	}
	printf("%07lx ", index);

	fclose(pfile);

	return 0;
}

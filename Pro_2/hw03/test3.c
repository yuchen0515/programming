#include <stdio.h>
#include <stdint.h>

int main(){

	FILE *pfile = NULL;

	if ((pfile = fopen("G4XUSR01.DAT", "rb")) ==NULL){
		printf("The file don't be opened!\n");
		perror("Error: ");
		return 0;
	}

	uint16_t temp = 0;
	uint64_t count = 0;

	while (!feof(pfile)){

		if (count != 0 && count %8 ==0) printf("\n");
		if (count % 8 == 0) printf("%07lx ", count*2);

		fread(&temp, 1, sizeof(uint16_t), pfile);
		printf("%04x ", temp);
		count +=1;
	}

	fclose(pfile);
	return 0;
}

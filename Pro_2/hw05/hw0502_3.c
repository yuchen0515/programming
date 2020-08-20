#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//0 => str
//1 => int
int32_t pp_open(FILE *pfile, char **ptr, char *str, int32_t num[], int32_t choice){
	int32_t count = 0;
	pfile = popen(str, "r");
	while (!feof(pfile)){
		if (choice == 0){
			fgets(ptr[count], 255, pfile);
			if (feof(pfile)) break;
			if (ptr[count][strlen(ptr[count])-2] == ':'){
				ptr[count][strlen(ptr[count])-2] = '\0';
			}else ptr[count][strlen(ptr[count])-1] = '\0';

			//printf("%s\n", ptr[count]);
		}else{
			fscanf(pfile, "%d", &num[count]);
			//printf("%d\n", num[count]);
		}
		count +=1;
	}
	pclose(pfile);
	return count;
}

int main(){

	FILE *pfile = NULL;
	int32_t *tx = calloc(256, sizeof(int32_t));
	int32_t *tx_tp = calloc(256, sizeof(int32_t));
	int32_t *rx = calloc(256, sizeof(int32_t)), count = 0;
	int32_t *rx_tp = calloc(256, sizeof(int32_t));


	char **inet = calloc(256, sizeof(char *)), *inett[256];
	for (int32_t i = 0 ; i < 256; i++){
		inett[i] = calloc(256, sizeof(char));
		inet[i] = inett[i];
	}

	char **title= calloc(256, sizeof(char *)), *titlee[256];
	for (int32_t i = 0 ; i < 256; i++){
		titlee[i] = calloc(256, sizeof(char));
		title[i] = titlee[i];
	}

	count = 0;
	int32_t check = 0;
	int32_t leng = 0;
	while (1){
		leng = pp_open(pfile, inet, "ifconfig | grep \'inet \' | awk {\'print $2\'}", tx, 0);
		pp_open(pfile, title, "ifconfig | grep -B 1 \'inet \' | grep \':\' | awk {\'print $1\'}", tx, 0);


		pp_open(pfile, title,"ifconfig | grep -A 6 \'inet \' | grep \'TX\' | grep \'bytes\'| awk {\'print $5\'}", tx, 1);

		pp_open(pfile, title,"ifconfig | grep -A 6 \'inet \' | grep \'RX\' | grep \'bytes\'| awk {\'print $5\'}", rx, 1);

		if (check == 1){
			printf("%d)\n", count);
			for (int32_t i = leng-1 ; i >= 0 ; i--){
				printf("%s (%s): TX: %dbps; RX: %dbps\n", title[i], inet[i], (tx[i]-tx_tp[i])*4, (rx[i]-rx_tp[i])*4);
			}

			sleep(2);
		}
		count +=1;
		check = 1;
		for (int32_t i = 0 ; i < leng ; i++){
			tx_tp[i] = tx[i];
			rx_tp[i] = rx[i];
		}
	}

	return 0;
}

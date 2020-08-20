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
		char temp[2048];
		fgets(temp, 2048, pfile);
		if (choice == 0){
			if (feof(pfile)) break;

			if (strstr(temp, "addr:")!=NULL){
				sscanf(temp, "addr:%s", ptr[count]);
			}else{
				sscanf(temp, "%s", ptr[count]);
			}
		}else{
			if (strstr(temp, "bytes:")!=NULL){
				sscanf(temp, "bytes:%d", &num[count]);
			}else{
				sscanf(temp, "%d", &num[count]);
				return 0;
			}
		}
		count +=1;
	}
	pclose(pfile);
	return count;
}

int main(){

	FILE *pfile = NULL;
	int32_t *tx = calloc(100005, sizeof(int32_t));
	int32_t *tx_tp = calloc(100005, sizeof(int32_t));
	int32_t *rx = calloc(100005, sizeof(int32_t)), count = 0;
	int32_t *rx_tp = calloc(100005, sizeof(int32_t));


	//double pointer
	char **inet = calloc(5000, sizeof(char *)), *inett[5000];
	for (int32_t i = 0 ; i < 5000; i++){
		inett[i] = calloc(5000, sizeof(char));
		inet[i] = inett[i];
	}

	char **title= calloc(5000, sizeof(char *)), *titlee[5000];
	for (int32_t i = 0 ; i < 5000; i++){
		titlee[i] = calloc(5000, sizeof(char));
		title[i] = titlee[i];
	}

	count = 0;
	int32_t check = 0, leng = 0;

	while (1){
		leng = pp_open(pfile, inet, "ifconfig | grep \'inet \' | awk {\'print $2\'}", tx, 0);
		pp_open(pfile, title, "ifconfig | grep -B 1 \'inet \' | grep \':\' | awk {\'print $1\'}", tx, 0);


		//檢查兩種版本的ifconfig
		if (pp_open(pfile, title,"ifconfig | grep -A 6 \'inet \' | grep \'TX\' | grep \'bytes\'| awk {\'print $6\'}", tx, 1) == 0){
			pp_open(pfile, title,"ifconfig | grep -A 6 \'inet \' | grep \'TX\' | grep \'bytes\'| awk {\'print $5\'}", tx, 1);
		}

		if (pp_open(pfile, title,"ifconfig | grep -A 6 \'inet \' | grep \'RX\' | grep \'bytes\'| awk {\'print $2\'}", rx, 1) == 0){
			pp_open(pfile, title,"ifconfig | grep -A 6 \'inet \' | grep \'RX\' | grep \'bytes\'| awk {\'print $5\'}", rx, 1);
		}

		if (check == 1){
			printf("%d)\n", count);
			for (int32_t i = leng-1 ; i >= 0 ; i--){
				printf("%s (%s): TX: %dbps; RX: %dbps\n", title[i], inet[i], (tx[i]-tx_tp[i])*4, (rx[i]-rx_tp[i])*4);
			}
		}
		count +=1;
		check = 1;
		for (int32_t i = 0 ; i < leng ; i++){
			tx_tp[i] = tx[i];
			rx_tp[i] = rx[i];
		}
		sleep(2);
	}

	return 0;
}

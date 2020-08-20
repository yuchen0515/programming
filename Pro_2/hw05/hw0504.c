#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

void strpt(char *dec){
	static char str[5000][500];
	char tpstr[5000];
	int32_t *check = calloc(5, sizeof(int32_t));
	static int32_t num = 0;
	
	if (strstr(dec, "ScheduleArrivalTime") !=NULL) check[0] = 1;
	if (strstr(dec, "DepartureAirportID") != NULL) check[1] = 1;
	if (strstr(dec, "ArrivalAirportID") != NULL) check[2] = 1;
	if (strstr(dec, "AirlineID") != NULL) check[3] = 1;
	if (strstr(dec, "FlightNumber") != NULL) check[4] = 1;
	
	if (!(check[0] | check[1] | check[2] | check[3] | check[4])){
		num = 0;
		return;
	}
	num +=1;

	strcpy(tpstr,strstr(dec, ":\""));
	tpstr[strlen(tpstr)-1] = '\0';

	if (check[0]) strcpy(str[0], tpstr+2);
	else if (check[1]) strcpy(str[1], tpstr+2);
	else if (check[2]) strcpy(str[2], tpstr+2);
	else if (check[3]) strcpy(str[3], tpstr+2);
	else if (check[4]){
		strcpy(str[4], tpstr+2);
		for (int32_t i = 0 ; i < 5; i++){
			if (strlen(str[i]) == 0) return;
			printf("%s", str[i]);
			
			if (i==1) printf("-->");
			else if (i == 4) printf("\n");
			else printf(" ");
		}
		num = 0;
	}
}


//定義option, enc=>e, dec=>d, output=>o
struct option long_options[] = {  
	{"arrival-time",  0, NULL, 't' },  
	{"flight-number", 0, NULL, 'f' },  
	{"airline-id", 0, NULL, 'a' },  
	{ 0, 0, 0, 0},  
};  

int main(int32_t argc, char *argv[]){
	int32_t c = 0, index = 0;
	int32_t record_t = 0, record_f = 0, record_a = 0;

	//處理參數
	while ((c = getopt_long(argc, argv, "tfa", long_options, &index)) != -1 ){
		switch( c ){
			case 't':
				record_t += 1;
				break;
			case 'f':
				record_f += 1;
				break;
			case 'a':
				record_a += 1;
				break;
			default:
				printf("Your argument input error!\n");
				printf("You should refer README.pdf!\n");
				return 0;
		}
	}
	if (argc != 2){
		printf("You should input one argument and refer README.pdf!\n");
		return 0;
	}

	if (!(record_t == 1 || record_f ==1 || record_a == 1)){
		printf("You should choice -t, or -f, or -a and refer README.pdf!\n");
		return 0;
	}

	FILE *pfile = NULL;
	if (record_t){
		if ((pfile = popen("./hw0504_2 1", "r"))==NULL){
			perror("Error: ");
			return 0;
		}
	}else if (record_f){
		if ((pfile = popen("./hw0504_2 2", "r"))==NULL){
			perror("Error: ");
			return 0;
		}
	}else if (record_a){
		if ((pfile = popen("./hw0504_2 3", "r"))==NULL){
			perror("Error: ");
			return 0;
		}
	}

	char str[3000];
	int32_t count = 0 ;
	while (!(feof(pfile))){
		str[count] = fgetc(pfile);		
		if (str[count] == ','){
			str[count] = '\0';
			count = 0;
			strpt(str);
		}
		count +=1;
	}

	pclose(pfile);

	return 0;
}

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

	FILE *pfile = NULL;
	char str[512];
	int32_t check = 0;

	int32_t rx = 0;
	int32_t tx = 0;
	int32_t rx2 = 0;
	int32_t tx2 = 0;

	int32_t count = 1;
	while (1){
		if ((pfile = popen("ifconfig", "r")) ==NULL){
			printf("Error end\n");
			exit(1);
		}
		int32_t tp_r = 0;
		int32_t tp_t = 0;

		if (check){
			system("");

		}

		while (fgets(str, 512, pfile)){
			printf("%s", str);
		}

		pclose(pfile);
		check = 1;
		sleep(1);
		count+=1;
	}




	return 0;
}

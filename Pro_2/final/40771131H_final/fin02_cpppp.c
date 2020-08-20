#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define int64_t long long int
 
int main(){

	char str[100], *token;
	const char spl[2] = " ";

	int32_t i = 0, delay = 2;
	int64_t sum = 0, idle = 0;
	int64_t last_sum = 0, last_idle = 0;

	long double idleFraction = 0.0;
 
	while (1){

		//開stat檔
		FILE* pfile = fopen("/proc/stat","r");
		fgets(str, 100, pfile);
		fclose(pfile);
		token = strtok(str, spl);

		//以空格做切割，取數字
		while (token != NULL){

			token = strtok(NULL, spl);

			if (token != NULL){
				//轉數字
				sum += atoi(token);

				if (i==3) idle = atoi(token);

				i+=1;
			}
		}

		//算usage
		long double ans = (idle - last_idle) * 1.0 / (sum - last_sum);
		ans = 1 - ans;
		ans *= 100;

		printf("CPU usage: %.2Lf %%\n", ans); 

		last_idle = idle;
		last_sum = sum;


		sleep(delay);
		i = 0;
	}	

	return 0;
}

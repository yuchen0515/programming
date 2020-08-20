#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define int64_t long long int
 
int main(){

	FILE *pfile = NULL;
	char str[256], cpu[5];

	int64_t user = 0 , nice = 0, idle = 0 , sys = 0;
	int64_t iowait = 0, irq = 0, softirq = 0;
	int64_t all_1 = 0, all_2 = 0, idle_1 = 0, idle_2 = 0;

	double usage = 0.0;
 
	while (1){

		//開stat檔
		FILE* pfile = fopen("/proc/stat","r");
		if (pfile == NULL){
			perror("Error: ");
			return 0;
		}

		fgets(str, 256, pfile);


		sscanf(str, "%s %lld %lld %lld %lld %lld %lld %lld", cpu, &user, &nice, &sys, &idle, &iowait, &irq, &softirq);

		all_1 = user + nice + sys + idle + iowait + irq + softirq;
		idle_1 = idle;

		fseek(pfile, 0L, SEEK_SET);
		sleep(1);

		memset(str, 0, sizeof(str));

		cpu[0] = '\0';

		user = 0;
		nice = 0;
		sys = 0;
		idle = 0;
		iowait = 0;
		irq = 0;
		softirq = 0;

		fgets(str, 256, pfile);
		sscanf(str, "%s %lld %lld %lld %lld %lld %lld %lld", cpu, &user, &nice, &sys, &idle, &iowait, &irq, &softirq);
		all_2 = user + nice + sys + idle + iowait + irq + softirq;

		usage = (double)(all_2-all_1 -idle_2 +idle_1);
		usage = (usage / (all_2 - all_1))/100;
		//usage *= 100;


		//算usage

		printf("CPU usage: %.2lf %%\n", usage); 

		fclose(pfile);
	}	

	return 0;
}

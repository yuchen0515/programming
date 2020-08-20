#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define int64_t long long int
 
int main(){

	FILE *pfile = NULL;
	char str[256], cpu[5];

	//一行內所有資料
	int64_t user = 0 , nice = 0, idle = 0 , sys = 0;
	int64_t iowait = 0, irq = 0, softirq = 0;

	//前面的全部+idle、後面的全部+idle
	int64_t all_1 = 0, all_2 = 0, idle_1 = 0, idle_2 = 0;

	//最終輸出的變數
	double usage = 0.0;
 
	while (1){

		//開stat檔
		FILE* pfile = fopen("/proc/stat","r");
		if (pfile == NULL){
			perror("Error: ");
			return 0;
		}

		fgets(str, 256, pfile);

		//sscanf直接拿資料
		sscanf(str, "%s %lld %lld %lld %lld %lld %lld %lld", cpu, &user, &nice, &sys, &idle, &iowait, &irq, &softirq);

		//第一階段全部加總
		all_1 = user + nice + sys + idle + iowait + irq + softirq;
		idle_1 = idle;

		//重新讀
		fseek(pfile, 0L, SEEK_SET);
		sleep(1);

		memset(str, 0, sizeof(str));


		user = 0;
		nice = 0;
		sys = 0;
		idle = 0;
		iowait = 0;
		irq = 0;
		softirq = 0;
		cpu[0] = '\0';

		//讀第二次
		fgets(str, 256, pfile);
		sscanf(str, "%s %lld %lld %lld %lld %lld %lld %lld", cpu, &user, &nice, &sys, &idle, &iowait, &irq, &softirq);
		
		//第二次加總
		all_2 = user + nice + sys + idle + iowait + irq + softirq;

		//usage算法 後減前，減一個idle差
		//再除以整體差*100
		usage = (double)(all_2-all_1 -idle_2 +idle_1);
		usage = (usage / ((all_2 - all_1)*1000));


		//輸出
		printf("CPU usage: %.2lf %%\n", usage); 

		fclose(pfile);
	}	

	return 0;
}

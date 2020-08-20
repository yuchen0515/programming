#include "readfile.h"
#include <stdio.h>
#include <stdint.h>

//字幕時間的格式
struct time{
	int32_t h;
	int32_t m;
	int32_t s;
	double ms;
}l,r;

//時間進位處理
int32_t carry(struct time *p){
	(p->s)+= ((int32_t)p->ms)/1000;
	p->ms = ((int32_t)p->ms)%1000;
	if ((p->ms) < 0){
		p->ms = 1000+(p->ms);
		p->s -= 1;
	}

	(p->m)+= (p->s)/60;
	p->s = (p->s)%60;
	if ((p->s) < 0){
		p->s = 60+(p->s);
		p->m -= 1;
	}

	(p->h)+= (p->m)/60;
	p->m = (p->m)%60;
	if ((p->m) < 0){
		p->m = 60+(p->m);
		p->h -= 1;
	}
	if ((p->h) <0){
		return 0;
	}
	return 1;
}

int main(){

	FILE *pfile = NULL, *Backup = NULL;
	char *str = calloc(2,sizeof(char));

	printf("Please enter the subtitle file: ");
	readget(str, 100, stdin, 0);

	//確認是否為.srt檔
	while ((pat_verify(str, "?*.srt") == 0)){
		printf("Your filename not ending by \".srt\"\n");
		printf("Please input again!\n");
		printf("Please enter the subtitle file: ");
		readget(str, 100, stdin, 0);
	}
	if ((pfile = fopen(str, "r")) ==NULL){
		printf("The file don't be opened!\n");
		perror("Error: ");
	}

	//先完全存入字串，再直接備份
	char *backup = calloc(strlen(str)+4, sizeof(char));
	int32_t i = 0;
	catstr(backup, str);
	catstr(backup, ".org");

	if ((Backup = fopen(backup, "w")) ==NULL){
		printf("The file don't be written!\n");
		perror("Error: ");
	}
	
	char bac[999999], pt[9999];
	int32_t count = 0, cho = 0, ind = 0;
	while (!(feof(pfile))){
		fscanf(pfile, "%c", (bac+count));
		count+=1;
	}
	*(bac+count) = '\0';

	fprintf(Backup, "%s", bac);
	fclose(Backup);
	fclose(pfile);

	pfile = fopen(str, "w");

	//決定是往前移還是往後
	printf("Forward Shift (1) or Backward Shift (2): ");
	scanf("%d", &cho);
	while (!(cho == 1 || cho ==2)){
		printf("Your input error! Please input again (1) or (2).\n");
		scanf("%d", &cho);
	}
	cho = cho==1 ? -1 : 1;

	double time = 0.0;
	printf("Shift time (sec): ");
	scanf("%lf", &time);

	count = 0;
	//是否會有無效時間
	int32_t che_ye = 1;

	//開始檢查格式，讀取並寫入原始檔案
	while (*(bac+count) != '\0'){
		if (*(bac+count) == '\n' || *(bac+count) =='\0'){
			*(pt+ind) = '\0';
			if (che_ye == 1 && pat_verify(pt, "??:??:??,??? --> ??:??:??,???")){
				sscanf(pt, "%d:%d:%d,%lf --> %d:%d:%d,%lf", &l.h, &l.m, &l.s, &l.ms, &r.h, &r.m, &r.s, &r.ms);
				l.s = l.s + cho*((int32_t)time);
				r.s = r.s + cho*((int32_t)time);
				l.ms = ((l.ms/1000) + cho*(time - (int32_t)time))*1000;
				r.ms = ((r.ms/1000) + cho*(time - (int32_t)time))*1000;
				int32_t tp_a = carry(&l), tp_b = carry(&r);
				if (tp_a ==0 || tp_b ==0){
					fprintf(pfile, "%s\n", pt);
					che_ye = 0;
					printf("Your time is nagetive, and the program wouldn't to shift your srt file!\n");
				}else fprintf(pfile, "%02d:%02d:%02d,%03d --> %02d:%02d:%02d,%03d\n", l.h, l.m, l.s, (int32_t)l.ms, r.h, r.m, r.s, (int32_t)r.ms);
			}else fprintf(pfile, "%s\n", pt);
			ind = 0;
		}else *(pt+(ind++)) = *(bac+count);
		count +=1;
	}

	fclose(pfile);
	if (che_ye) printf("Done!\n");

	return 0;
}

#include <stdio.h>		//引入標頭檔<stdio.h>以便標準輸入和輸出
#include <stdint.h>		//引入標頭檔<stdint.h>以便使用標準整數型態
#include <stdlib.h>		//引入標頭檔<stdlib.h>以便後續使用system("clear")的指令
#include <unistd.h>		//引入標頭檔<unistd.h>以便後續使用usleep的指令

/*
	副函式：shift
	參數：陣列、陣列的大小、現在指向的記憶體位置、陣列尾段的記憶體位置、毫秒
	回傳：無
	執行：從目前位置引到陣列最末段，再回到前面往後印，直到指向剛開始的記憶體位置就結束
	例子：陣列有0123456789，目前指向5，輸出5678901234(56789／01234)
*/
void shift(int32_t arr[], int32_t *now, int32_t *ptr, int32_t msec){

	//也可使用size處理這邊，size為10，now指標記錄目前位置，ptr則記錄arr最末位置
	//跑10次，當now等於ptr的位置就讓now移到最前即可
	//這邊為少傳一次參數，再設定cur指標

	int32_t *cur = now;
	//now指標為原始位置，cur指標記錄目前位置
	//當now再次等於cur時就停止，但剛開始cur必定等於now，所以用do-while讓他先跑一次
	//用while做也可以，但會比較冗長

	do{
		fprintf(stderr,"%d",*cur);
		//printf("%d",*cur);	//印出目前位置的數值
		if (cur==ptr){	//如果目前位置在陣列最末段，則移到陣列最前方
			cur = arr;
		}else{
			cur++;		//其他情況都將cur進一個int32_t的記憶體長度
		}
	}while(cur!=now);	//當cur!=now時就繼續跑，所以理論上會跑10次(以這題而言)
	usleep(msec);	//跑完會印十個數字，此時會休眠msec秒
	
	//不使用指標直接用陣列做也可以，但因為陣列每次都要往左位移一格，改十次數字效率會變很差
}

int main(){		//主函式的進入點

	int32_t size = 10;		//0123456789共十個數字

	//宣告arr陣列存0123456789
	int32_t arr[size];		
	for (int32_t i=0; i<size; i++){
		arr[i] = i;
	}
	
	//now放arr最前段記憶體位置, ptr指向陣列記憶體末段
	int32_t *now = &arr[0], *ptr = &arr[9];
	uint32_t msec = 0;

	//輸入毫秒
	printf("Please enter the time interval (1-1000 msec): ");
	scanf("%u", &msec);

	//檢查使用者輸入
	while (!(msec>=1 && msec<=1000)){
		printf("Input error! your values isn't on [1,1000]\n");
		printf("Please enter the time interval (1-1000 msec): ");
		scanf("%u", &msec);
	}

	while (1){

		system("clear");	//清除螢幕後開始印

		shift(arr, now, ptr, msec*1000);	
		//printf("\n");

		if (now==ptr){
			now = arr;
		}else{
			now++;
		}
		//usleep(msec*950);

		//因usleep是微秒，所以這邊50+950總和共1000 (微秒*1000 = 毫秒)
		//這邊發現如果usleep不分兩次的話，跑馬燈會沒有效果
		//必須利用一個在螢幕上速度會稍微"慢"的指令(換行)
		//並且兩個usleep在前後分兩段才行
		//如上面所寫的方式，會造成顯示0.95秒，螢幕清除0.05秒的效果

		//另發現fprintf因為是採用直接輸出的方式，也可以使用

	}

	return 0;

}

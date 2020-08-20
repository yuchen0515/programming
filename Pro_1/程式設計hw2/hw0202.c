#include <stdio.h>	//引入標頭檔<stdio.h>以便標準輸入、輸出
#include <stdint.h> //引入標頭檔<stdint.h>以使用標準整數型態

int main(){		//提示主函數的進入點
	
	int32_t dis = 0;	//宣告儲存距離(m)的變數
	int32_t stop = 0;	//宣告儲存停滯秒數(s)的變數
	int32_t state = 0;	//宣告紀錄新年／夜間期間的變數	
	int32_t fare = 70;	//宣告費用變數，從70起跳
	
	//提示使用者輸入計程車搭乘距離
	printf("Please enter the taxi driveing distance (meter) : ");
	//讀取使用者輸入的距離至dis變數內
	scanf("%d",&dis);
	//考慮到使用者可能輸入負數，故設此防護機制
	while (dis < 0){
		printf("input error!\nplease enter a positive distance (meter) again: ");
		scanf("%d", &dis);
	}

	//當距離大於1250時，計算一段新路程(剛開始)即跳表
	//如1251時，跳表5元，一直到1500m
	if (dis > 1250){
		int temp= dis-1250;	//我們只需要知道大於1250的那段長度是多少
		fare = fare + 5* (temp/250);	//先計算有幾個是「全滿」的250m路段
		if (temp%250!=0){	//若有未滿250的路程，加5元
			fare = fare + 5;
		}
	}
	//提示使用者輸入停滯時間秒數
	printf("Please enter the taxi stopping time (second) : ");
	//讀取使用者輸入的停滯時間
	scanf("%d",&stop);

	while (stop < 0){
		printf("input error!\nplease enter a stopping time (second) again: ");
		scanf("%d", &stop);
	}

	//每滿100即跳表一次，(如100m跳5元，200m共跳10元)
	//不需判斷是否大於等於100，若99秒，則(stop/100)=>(int)0.99=>0
	fare = fare + 5*(stop/100);
	
	//紀錄共有幾個state是為1的儲存進i變數內
	int i = 0;
	//提示使用者輸入是否在夜間時間搭乘
	printf("Is nighttime or not (0: No, 1: Yes): ");
	scanf("%d",&state);
	if (state!=0)
		i = i + 1;		//讀入state後，無論是0或1都存進i變數內

	//提示使用者輸入是否在新年期間搭乘
	printf("Is Chinese New Year or not (0: No, 1: Yes): ");
	scanf("%d",&state);
	if (state!=0)
		i = i + 1;		//讀入state後，無論是0或1都存進i變數內

	fare = fare +20*i;	//將fare加i*20，即若夜間、新年都成立，i則為2=>+40元
	
	//如果搭乘距離為0，表示根本沒開車，不應收錢
	if (dis ==0)	fare = 0;

	//輸出計程車費為多少
	printf("Taxi fare: %d\n",fare);

	return 0;	//回傳0以跳出主函數
}

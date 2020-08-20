#include <stdio.h>	//引入標頭檔<stdio.h>以便標準輸入和輸出
#include <stdint.h>	//引入標頭檔<stdint.h>使用標準整數型態

int main(){		//提示主函數之進入點

	/*
		start, s1~s6, final 以1或0紀錄是否在該狀態
		count紀錄已經跑到第幾個數字，current則依據count數值分別給予a,b,c,d,e的數值進current
		a,b,c,d,e則負責儲存使用者輸入的五個整數
	   */
	int32_t start=1, s1=0, s2=0, s3=0, s4=0, s5=0, s6=0, final=0;
	int32_t count=0, current=0;
	int32_t a=0, b=0, c=0, d=0, e=0;
	
	//提示使用者輸入五個整數，並且分別讀進a,b,c,d,e內
	printf("Please enter 5 integers: ");
	scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);

	//設置一個無限迴圈，其中當數字讀到第五個數結束後便會跳出迴圈
	while (1){
		//count等於0~4，依序將current= a,b,c,d,e的數值
		switch (count){
			case 0:
				current = a;
				break;
			case 1:
				current = b;
				break;
			case 2:
				current = c;
				break;
			case 3:
				current = d;
				break;
			case 4:
				current = e;
				break;
			default:
				current = 0;
				break;
		}
		//如果狀態是在state的話，就進入該switch
		if (start==1){
			switch (current){
				//依據current判別，若等於10或35則將start狀態關閉，開啟s1
				//並將count加1，以便讀入下一個數
				case 10:
				case 35:
					s1=1;
					start=0;
					count=count+1;
					break;
				//等於11時，開啟s3狀態，並將start關掉，count加1以便讀入下一個數
				case 11:
					s3=1;
					start=0;
					count=count+1;
					break;
				//等於20或78時，開啟s5狀態，並將start關掉，count+1以便讀取下個數
				case 20:
				case 78:
					s5=1;
					start=0;
					count=count+1;
					break;
				//若是除了10,35,11以外的任意數，則start狀態開著，只將count+1讀入下個數
				default:
					count=count+1;
					break;
			}
		}
		else if (s1==1){	//如果s1狀態是true則進入
			switch (current){	//依current的數值去switch
				case 12:	//如果是12,36的話，s6狀態開啟並將s1關閉，將count+1讀入下個數
				case 36:
					s6=1;
					s1=0;
					count=count+1;
					break;
				//若數值為19，s2狀態開啟，s1狀態關閉，並將count+1以便讀入下個數
				case 19:
					s2=1;
					s1=0;
					count=count+1;
					break;
				//除了12,36,19以外，其他數一律回到s1狀態，並將count+1以便讀入下個數
				default:
					count=count+1;
					break;
			}
		}
		else if (s2==1){	//如果s2狀態是true則進入
			switch (current){	//依據current的數值去switch
				case 99:	//當數值為99時，將final狀態開啟，s2狀態關閉，並將count+1讀入下個數
					final=1;
					s2=0;
					count=count+1;
					break;
				case 43:		//當數值為43，則回到s2狀態，先將count+1以便讀入下個數
					count=count+1;
					break;
				default:		//當數值為99,43以外，則start狀態開啟，s2關閉並將count+1讀入下個數
					s2=0;
					start=1;
					count=count+1;
					break;
			}
		}
		else if (s3==1){	//如果s3狀態是true則進入
			switch (current){	//依據current的數值去switch
			default:	//所有數，都進到s4，並將count+1以便讀入下個數
					s3=0;
					s4=1;
					count=count+1;
					break;
			}
		}
		else if (s4==1){	//如果s4狀態是true則進入
			switch (current){	//依據current的數值去switch
				default:	//所有數都進入到s6狀態，並將count+1以便讀入下個數
					s4=0;
					s6=1;
					count=count+1;
					break;
			}
		}
		else if (s5==1){	//如果s5狀態是true則進入
			switch (current){	//依據current的數值去switch
				case 1:	//如果為1，則進入到s4的狀態，並將count+1以便讀入下個數
					s4=1;
					s5=0;
					count=count+1;
					break;
				case 2:	//如果為2，則進入到s6的狀態，並將count+1以便讀入下個數
					s5=0;
					s6=1;
					count=count+1;
					break;
				default:	//如果數值為1,2以外，則一律進到start狀態，並將count+1以便讀入下個數
					s5=0;
					start=1;
					count=count+1;
					break;
			}
		}
		else if (s6==1){	//如果s6狀態為true，則進入
			switch (current){	//依據current的數值去switch
				case 108:		//數值為108則進到final狀態，並將count+1以便讀入下個數
					final=1;
					s6=0;
					count=count+1;
					break;
				default:	//數值不是108則一律進到s5狀態，並將count+1以便讀入下個數
					s6=0;
					s5=1;
					count=count+1;
					break;
			}
		}
		else if (final==1){		//如果final狀態為true則進入
			switch (current){	//所有數值都回到final，並將count+1以便讀入下個數
				default:
					count=count+1;
					break;
			}
		}
		//不屬於上面的if-else，最終直接判斷是否讀過五個數，如果是則跳出迴圈
		if (count==5)	break;	
	}

	//輸出前半文字
	printf("The user is in the ");

	//判斷狀態是在哪一個，則輸出
	if (start==1)	printf("start ");
	else if (s1==1)	printf("S1 ");
	else if (s2==1)	printf("S2 ");
	else if (s3==1)	printf("S3 ");
	else if (s4==1)	printf("S4 ");
	else if (s5==1)	printf("S5 ");
	else if (s6==1)	printf("S6 ");
	else if (final==1)	printf("final ");
	else printf("unknow ");

	//輸入後半文字
	printf("state.\n");

	return 0;	//回傳數值0以便跳出主函數
}

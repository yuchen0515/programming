#include <stdio.h>
#include <stdint.h>

//matrix operation的三種運算

//1. 列交換
void exc(double row[], double row2[], int32_t num){
	for (int32_t i = 0 ; i < num+1 ; i++){
		double temp = row[i];
		row[i] = row2[i];
		row2[i] = temp;
	}
}

//2. 列常數乘法
void sca(double row[], double c, int32_t num){
	for (int32_t i = 0 ; i < num+1; i++){
		row[i] *= c;
	}
}

//3. 列運算
void ope(double row[], double row2[], double c, int32_t num){
	for (int32_t i = 0 ; i < num+1 ; i++){
		row2[i] = row2[i] + row[i] * c;
	}
}

int main(){
	
	int32_t num = 0;

	//變數數量的讀取與檢查使用者輸入
	printf("Please enter the variable number: ");	
	scanf("%d", &num);

	while (!(num > 0)){
		printf("Input Error! Your value should be over zero\n");
		printf("Please enter the variable number: ");	
		scanf("%d", &num);
	}

	//設置檢查 無解、無限多組解的變數
	int32_t no_sol = 0;
	int32_t many_sol[num];
	for (int32_t i = 0 ; i < num ; i++){
		many_sol[i] = 0;
	}

	//讀入使用者輸入的方程式(二維陣列)
	double arr[num][num+1];

	for (int32_t i = 0 ; i < num ; i++){

		printf("Please enter the ");

		if (i==0) printf("1st ");
		else if (i==1) printf("2nd ");
		else if (i==2) printf("3rd ");
		else printf("%dth ", i+1);
		printf("equation (%d numbers): ", num+1);
		for (int32_t j = 0 ; j < num+1; j++){
			scanf("%lf", &arr[i][j]);
		}

	}

	//如果只有一個變數要額外處理
	if (num==1){
		if (arr[0][0]!=0){
			sca(arr[0], 1/arr[0][0],num);
		}else{
			if (arr[0][1]==0){
				many_sol[0] = 1;
			}else{
				no_sol = 1;
			}
			
		}

		
	}else{
		//跑一個i 一個j，交互檢查
		//若該列領導係數為0，要往下找領導係數不為0的跟他交換
		int32_t index = 0 ;
		
		for (int32_t i = 0 ; i < num-1; i++){
			if (arr[index][i]==0){
				for (int32_t j=index+1; j<num ;j++){
					if (arr[j][i] !=0){
						exc(arr[index],arr[j],num);
						break;
					}
					
					if (j==num-1){	
						//進到這表示該行全部都是0，有無限多組解
						many_sol[i] = 1;	
					}
				}
			}
			//該行都是0就可以不用計算了，繼續下一個
			if (many_sol[i]==1) continue;
			
			//如果不是這樣，就先把領導係數變1
			sca(arr[index], 1/arr[index][i], num);
			//開始往下消，把下面的領導係數全部變0，留下自己
			for (int32_t j = index+1; j < num ; j++){
				if (arr[j][i] ==0) continue;
				ope(arr[index], arr[j], (arr[j][i]/arr[index][i])*-1, num);
			}
			index++;
		}
		//如果該行沒有全部都為0，就可以做scaling
		if (arr[num-1][num-1] ==0) many_sol[num-1] =1;
		if (many_sol[num-1]==0) sca(arr[num-1], 1/arr[num-1][num-1], num);

		//同樣的，由下往上消 back pass
		index =num-1-many_sol[num-1];
		for (int32_t i=num-1 ; i>0 ; i--){
			if (many_sol[i]==1){
				if (arr[i][i] ==0 && arr[i][num]!=0)	no_sol =1 ;
				continue;
			}
			
			for (int32_t j = index-1; j>=0; j--){
				ope(arr[index], arr[j], (arr[j][i]/arr[index][i])*-1, num);
			}

			if ((arr[i][i]==0 && arr[i][num]!=0)|| (arr[0][0]==0 && arr[0][num]!=0)){
				no_sol = 1;
				break;
			}

			index--;
		}
	}

	//輸出答案
	printf("Answer:\n");	
	for (int32_t i = 0 ; i < num ; i++){
		//無解直接輸出沒答案
		if (no_sol == 1){
			printf("The equation isn't solution.\n");
			break;
		}
		printf("x%d = ",i+1);
		//該變數有無限多組解輸出free (free variable)
		if (many_sol[i] == 1){
			printf("free\n");
		}else{
			//不然就印出他的答案出來
			printf("%d\n",(int)arr[i][num]);
		}
	}
	
	return 0;
}

#include <stdio.h>	//引入標頭檔<stdio.h>，以便標準輸入和輸出
#include <stdint.h>	//引入標頭檔<stdint.h>，以便使用標準整數型態

//快速幕
//盡量利用位元運算，提高performance
int32_t pow_(int32_t x, int32_t y){

	if (y==0) return 1; 	//y==0時回傳1
	if (!(y&1)) return pow_(x, y>>1) * pow_(x, y>>1); //y為偶數時回傳y/2次方*y/2
	else return pow_(x, y>>1) * pow_(x, y>>1) * x; //y為奇數時，額外再乘上x

}

int main(){		//提示主函式進入點

	//設定變數"degree"和檢查變數範圍的check函式
	int32_t check = 0, degree = 0;
	size_t i = 0;

	//提示使用者輸入一個非負的整數(次方)
	printf("Please enter a non-negative drgree: ");
	scanf("%d", &check);

	//檢查使用者輸入的次方是否為非負，若否則提示使用者重新輸入
	while (!(check >=0)){
		printf("Input error! your value isn't over the zero.\n");
		printf("Please enter a non-negative drgree: ");
		scanf("%d", &check);
	}

	//將檢查好的check變數，數值丟到degree內
	degree = check;
	//先讀好大小，再宣告陣列，才能知道陣列要開多大
	//宣告係數陣列為(degree+1)
	int32_t coe[degree+1];

	//提示使用者輸入係數(並提示使用者須輸入的個數)
	printf("Plese enter the coefficients ( %d number ): ", degree + 1);

	//重新讀取degree+1個係數進coe陣列
	for (i = 0; i<=degree; i++){
		scanf("%d", &coe[i]);
	}

	//提示使用者輸入欲代入的數值
	int32_t x = 0;
	printf("Please enter x: ");
	scanf("%d", &x);

	//外迴圈 (每次輸出一次f^[]() = ?) 輸出[degree+1]次
	for (i = 0 ; i<=degree; i++){

		int32_t res = 0;	//作為紀錄數值總和的變數

		//跑degree-i次，因為每微分一次就會少一項
		for (size_t j = 0; j<=degree-i; j++){
			//若i!=0才開始微分，並依序以係數*次方取代原本的數值
			if (i!=0) coe[j] = coe[j] * (degree - i - j + 1);
			//計算函式各項的數值，依序加進res中
			res += (coe[j] * pow_(x, degree - i - j));
		}
		printf("f");
		//若非為原函式，則會輸出微分到第幾階
		if (i!=0) printf("^%ld",i);
		//輸入代入的數值，和結果(此處將一句分開，能使程式碼較簡短)
		printf("(%d) = %d\n", x, res);
	}

	return 0;
}

#include <stdint.h>	//引入標頭檔<stdint.h>，以便標準輸入輸出
#include "hw0401_header.h"	//引入自製標頭檔"hw0401_header.h"以便使用hanoi_for函數

//遞迴版hanoi
void hanoi_re(int32_t index, int32_t rod1, int32_t rod2, int32_t rod3){
	
	if (index != 1){

		/*
		從1往後演算，我們可以發現一件事
		搬兩個時，都是固定的程序
		搬三個時，是先搬兩個到輔助柱上，再把第三個搬到目的地
		接著再把兩個從輔助柱上移到目的地
		搬四個則，三個→輔助柱，第四個→目的地，三個→目的地
		因此會發現固定的結構，n-1到達輔助柱，第n到目的地，再把n-1從輔助柱到目的地
		所以可以寫成下列三行的形式
		*/

		hanoi_re(index-1, rod1, rod3, rod2);
		printf("move disk %d to rod %d\n", index, rod2);
		hanoi_re(index-1, rod3, rod2, rod1);

	}else{

		/*
		我們搬兩個時，disk 1→rod3，disk 2→rod 2，此時上方就停了
		這時應是搬disk1→rod 2，因此我們把最後一個動作補上去
		(我們從上方結構看，會發現後面的hanoi_re(index-1,rod3,rod2,rod1)
		跑到最後一輪時，應會少輸出一次，所以要補回來
		*/
		printf("move disk %d to rod %d\n", index, rod2);

	}
	
}

//此函式是為hanoi的迴圈版所寫
//大致上是由n是奇數或偶數,決定它的位置改變方式
int32_t shift(int32_t n, int32_t pos, int32_t sh){

	//在sh為1情況下，n為奇數則pos往右，偶數則pos往左
	//在sh為-1情況下，n為奇數則pos往左，偶數則pos往右
	if (n&1){

		if (pos+sh == 3) return 0;
		if (pos+sh == -1) return 2;
		return pos+sh;

	}else{

		if (pos-sh == 3) return 0;
		if (pos-sh == -1) return 2;
		return pos-sh;

	}
}

//迴圈版hanoi，傳入n和rod的狀態(二維)
void hanoi_for(int32_t n, int32_t rod[][20]){ 

	int32_t num[3] = {n, 0, 0};	//存個柱子的盤子數
	int32_t cos[3] = {21, 21 ,21};	//temp(暫存數)寫成陣列，作為比較盤子大小的方式
	int32_t cur = 1, disk = 0;	//目前設在第1+1根柱子
	int32_t ptr = 0, dir = 0;	//ptr原始位置，dir目的位置

	while (num[1]!=n){	//當第二根柱子的盤子數等於n則終止

		//上一次移到的那個柱子，就不要再移動，因此選擇該柱子以外的兩個分別存進upp,low內
		int32_t upp = shift(21, cur, 1);
		int32_t low = shift(21, cur, -1);

		//若該柱子沒有盤子，把比較的數設為21，反之則設為該柱子最小的盤子
		if (num[low] == 0) cos[low] = 21;
		else cos[low] = rod[low][num[low]-1];
		if (num[upp] == 0) cos[upp] = 21;
		else cos[upp] = rod[upp][num[upp]-1];

		//因此我們可以透過這樣選擇較小的為我們要移動的盤子(柱子)
		ptr = cos[low] <= cos[upp] ? low : upp;
		disk = cos[ptr];

		//發現，要移動的盤子在第一根或第二根柱子時
		//奇數則往右移動，偶數往左移動
		//當要移動的盤子在第三根柱子時，則相反
		//奇數往左移動，偶數往右移動，因此寫成下列式子
		//其中dir為目的地
		if (ptr!=2) dir = shift(num[ptr], ptr, 1);
		else dir = shift(num[ptr], ptr, -1);
		
		//單純輸出，並把柱子狀態改變，以及各柱子數量改變，最終把cur設為目的地(dir)
		printf("move disk %d to rod %d\n", disk, dir+1);

		rod[dir][(num[dir]++)] = rod[ptr][num[ptr]-1];
		rod[ptr][(num[ptr]--)-1] = 0;

		cur = dir;
	}
}

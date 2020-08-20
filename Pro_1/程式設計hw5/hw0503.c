#include <stdio.h>
#include <stdint.h>

//eyesfun_bool=> 牌輪流當眼(門) 若該牌可胡就記為1
//onetwo_bool=> 去掉一對以後，開始檢查可不可胡，可=>1，不可=>0
int32_t eyesfun_bool = -1, onetwo_bool = -1;

//two_check=> 檢查一副牌某張牌恰只有兩張的有幾組
//兩組=>必定不胡／一組=>只抓該組為一對，檢查胡牌，不可直接回傳0，不用多跑了
//一組時，會記錄該組花色的索引值為two_index=>一組時就直接跑這個索引
int32_t two_check = 0, two_index = -1;

//絕對值函數
int32_t abs(int32_t t){
	if (t<0) return -t;
	return t;
}

//陣列複製函數
void copy(int32_t arr1[], int32_t arr2[], int32_t size){
	for (int32_t i = 0 ; i < size; i++) arr2[i] = arr1[i];
}

//胡牌檢驗函數(只檢查順、刻、槓)[遞迴]
//為DFS的寫法，深度搜索後發現可以就直接回傳
void onetwo(int32_t ma[],int32_t index, int32_t size, int32_t sum, int32_t kong){

	//如果總張數已經為0了代表能胡，就回傳
	if (sum==0){
		onetwo_bool = 1;
		return;
	}

	//索引值已經是-1就跳回去(像樹的結構)
	if (index ==-1) return;

	//索引值在正常範圍的話，該張數==0就繼續往前掃
	if (index>=0 && ma[index]==0){
		onetwo(ma,index-1,size,sum, kong);
		return;
	}

	//複製一下ma陣列
	int32_t reg[size];
	copy(ma,reg,size);

	//張數==1, ==2或 為四張的索引值為1，就跑進來跑順子的判斷式
	//跑順子
	if ((reg[index]==1 || reg[index] == 2)||(kong ==1 && reg[index] == 4)){
		//如果是東南西北、白板、中、發等等 就不可能跑順
		if ((index>=2 && index<=8)|| (index>=11 && index<=17) || (index>=20 && index<=26)){
			//如果可以跑，就繼續跑，此外如果是靠 ==1,==2以外的方式進來，就把kong-1
			if (reg[index]>0 && reg[index-1]>0 && reg[index-2]>0){
				//1張，2張，4張，跑完順時
				//一張要繼續往前掃，2張,4張停在原本索引值
				//所以寫成index-temp，其中temp = |2-張數|%2
				//例如2張=>temp=0，4張=>temp=0，1張=>temp=1
				//發現這兩種式子可以通用，可節省很多if-else判斷
				int32_t temp = abs(2-reg[index])%2;
				reg[index]--; reg[index-1]--; reg[index-2]--; sum-=3;
				onetwo(reg,index-temp,size,sum,(kong-(kong ==1 && reg[index] ==3)));
				return;
			}else{
				//kong>0就回傳，讓他繼續跑"槓"的部分
				if (kong>0) return;	
				//不處於kong的狀態就回傳"不可以胡"
				onetwo_bool = 0;
				return;
			}
		}
	//張數==3
	//只檢查刻，如果要以順的方式消掉三張，必定是三張連號的順，那也可以用刻去檢查
	//如333444555，我可以345,345,345，也可以直接333,444,555
	//若有22333444555=>23344555=>234555=>555=>0，所以我檢查刻的優先順位大於順是沒問題的
	}else if (reg[index] ==3){
		//直接往前掃
		reg[index]-=3; sum-=3;
		onetwo(reg,index-1,size,sum,kong);
		return;
	//張數==4
	//先跑 把他當順，可以就繼續跑的情況(順=>4-1=3=>刻=>0繼續跑)
	//發現不行=>當槓=>不行=>return;
	}else if (reg[index] ==4){

		onetwo(reg,index,size,sum,kong+1);
		//如果發現可以胡牌了就跳出去
		if (onetwo_bool == 1) return;

		//不行就跑當槓的部分
		reg[index]-=4; sum-=4;
		onetwo(reg,index-1,size,sum,kong);

		//可就回傳可以，不可就回傳不可
		if (onetwo_bool ==1) return;
		if (kong==0) onetwo_bool = 0;
		return;
	}
	
	//會到這邊代表不屬於筒條萬(風、中發白)，又跑不了刻
	onetwo_bool = 0;
	return;
}

//眼睛函數(遞迴)
void eyes_fun(int32_t ma[], int32_t index, int32_t size, int32_t sum, int32_t kong, int32_t eyes[]){
	//因為函數傳陣列是直接傳送陣列的記憶體位置，因此會直接改到陣列的數值
	//所以要在函數內額外再加一個陣列並"複製"原有陣列，只改該陣列就不會改到原本陣列的數值
	int32_t eye2[size], reg[size];
	copy(eyes,eye2,size); copy(ma, reg, size);

	//如果一副牌恰(只)有一個tile等於2，只跑一次(不行當然就不能胡牌)
	if (two_check == 1){
		reg[two_index]-=2; sum-=2;

		int32_t tmp = onetwo_bool;	//為了防止判斷完onetwo_bool之後，數值變不回去，先存
		onetwo(reg,33,size,sum,kong);

		if (onetwo_bool ==0) eyesfun_bool = 0;
		else eyesfun_bool = 1; 

		onetwo_bool = tmp;	//恢復原本數值(判斷完後)
		return;
	}

	//如果由後往前掃，掃完了index==-1，都還沒回傳出去，代表不可胡啦
	if (index==-1){
		eyesfun_bool = 0;
		return;
	}

	//索引值在正常範圍內，而且該索引不能當門，就繼續往前跑
	if (index>=0 && eye2[index]==0){
		eyes_fun(ma,index-1,size,sum,kong,eye2);
		return;
	}

	//到這代表索引值在正常範圍，且可以當門，就跑跑看
	//張數、總和先扣掉，因為跑過了把紀錄可以當門的索引變0
	reg[index]-=2; sum-=2;
	eye2[index]=0;

	int32_t temp = onetwo_bool;
	//跑看看
	onetwo(reg,33,size,sum,kong);

	//可以就回傳
	if (onetwo_bool==1){
		eyesfun_bool = 1;
		return;
	}

	//不行就把數值加回去
	onetwo_bool = temp; sum+=2;

	//這裡之所以傳進去的是ma，是因為可以不用加回去reg[index]，ma就是原本的陣列
	//而每個eyes_fun裡面都不會改到原本的陣列
	//不行就繼續往前跑
	eyes_fun(ma,index-1,size,sum,kong,eyes);	
	return;
}

//主函數
int main(){

	//使用者輸入(check), 目前牌總和(sum)
	int32_t check = 0, sum = 0;
	//紀錄該索引可否當門(一對)，可=>1，不可=>0 (eyes[34])
	//紀錄每個索引的牌有幾張 (mah[34])
	int32_t eyes[34] = {0}, mah[34] = {0};

	//使用者輸入
	while (check != -1){

		printf("Please enter the tile: ");
		scanf("%d", &check);

		//檢查範圍
		while (!(check>=1 && check<=34)){
			if (check == -1) break;
			printf("Input error! your value isn't on [1,34]\n");
			printf("Please enter the tile: ");
			scanf("%d", &check);
		}

		if (check == -1) break;

		//如果輸入不是-1，就讓索引+1(張數)／總和+1
		mah[check-1]++; sum++;

		//輸入的索引張數已經大於4，就提示使用者重新輸入(麻將每個tile只有四張)
		if (mah[check-1]>4){
			printf("Input error! Encode %d is over 4 tile.\n", check);
			//把多加的減回去
			mah[check-1]--; sum--;
		}
	}

	//檢查有幾個tile>=2張
	for (int32_t i = 0 ; i < 34; i++){
		if (mah[i] ==2){
			eyes[i] = 2;
			two_check +=1;
			if (two_check==1) two_index = i;
		}else if (mah[i] >2) eyes[i] = 1;
	}

	//跑一次胡牌程式
	eyes_fun(mah,33,34,sum,0,eyes);

	//牌數少於17必定不胡，如果eyesfun_bool=0也是不胡，除此之外為胡牌
	if (sum<17 || !(eyesfun_bool)) printf("Not a Winning Hand.\n");
	else printf("Winning Hand.\n");
		
	return 0;
}

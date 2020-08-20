#include "rational.h"

//交換數字
void swap(int32_t *a, int32_t *b){
	int32_t temp = *a;
	*a = *b;
	*b = temp;
}

//找最大公因數
//若其中一數為0，則回傳-1
//負數則先轉正數再計算
int32_t gcd(int32_t a, int32_t b){
	if (a==0 || b==0) return -1;

	if (a < 0) a = -a;
	if (b < 0) b = -b;

	if (b > a) swap(&a, &b);
	while (b!=0){
		int32_t temp = a%b;
		a = b;
		b = temp;
	}

	return a;
}

//紀錄分數中的負號有幾個
int32_t rational_neg(const struct rational r1){
	int32_t reg = 0;
	if (r1.num < 0) reg+=1;
	if (r1.don < 0) reg+=1;
	return reg%2; //負負得正
}

//分數的絕對值
void rational_abs(struct rational *r){
	if (r->num < 0) r->num = -(r->num);
	if (r->don < 0) r->don = -(r->don);
}

//此題測資為hw0104.c附，然呼叫本函式，p,q型態為int32_t
//若助教使用特殊測資，如1i,9d等，編譯時即無法通過
//1i,9d=>error, "1i","9d"=>warning
//若僅輸入 i, p，則系統將其acsii碼當成數字去計算故無影響
int32_t rational_set(struct rational *r, int32_t p, int32_t q){
	r -> num = p;
	r -> don = q;

	//分母為0回傳-1
	if (r->don==0){
		return -1;
	}

	//先記錄負數有幾個
	int32_t neg = rational_neg(*r);
	rational_abs(r);
	
	if ((r->num)==0) r->don = 1;
	else{
		//化為最簡分數：找兩者最小公因數並同除以該數
		int32_t tp = gcd(r->num,r->don);
		//
		//printf("tp: %d\n",tp);
		r -> num = (r->num)/tp;
		r -> don = (r->don)/tp;
	}

	//統一設置負號在分子位置
	if (neg==1) r->num = -(r->num);

	return 0;
}
// return -1 if invalid; other wise, return 0.


//分母為0則輸出不可，反之輸出分子、分母
int32_t rational_print(const struct rational r){
	if (r.don == 0) printf("Sorry, your donominator is zero.\n");
	else printf("(%d,%d)\n", r.num, r.don);
}
// in the form of (p,q)



//前後相加，主要是通分要好好處理，分母任一為零就要提示輸入錯誤
void rational_add(struct rational *r, const struct rational r1, const struct rational r2){
	int32_t don = 0, num = 0;
	int32_t tp = gcd(r1.don, r2.don);

	//只要兩者分母都不是零就可以正常運算
	if (tp!=-1){
		don = (r1.don * r2.don) / tp;
		num = r1.num *(don/r1.don) + r2.num *(don/r2.don);
	}
	rational_set(r, num, don);
}


//前減後面，主要是通分要好好處理，分母任一為零就要提示輸入錯誤
void rational_sub(struct rational *r, const struct rational r1, const struct rational r2){
	int32_t don = 0, num = 0;
	int32_t tp = gcd(r1.don, r2.don);
	if (tp!=-1){
		don = (r1.don * r2.don) / tp;
		num = r1.num *(don/r1.don) - r2.num *(don/r2.don);
	}
	rational_set(r, num, don);
}

//單純相乘而已，要注意就是化為最簡分數
void rational_mul(struct rational *r, const struct rational r1, const struct rational r2){
	int32_t num = r1.num * r2.num;
	int32_t don = r1.don * r2.don;
	rational_set(r, num, don);
}

//單純乘以倒數而已，但最後要化為最簡分數，並確認分母是否為零
//在set函數中已經做了後面的事情
void rational_div(struct rational *r, const struct rational r1, const struct rational r2){
	int32_t num = r1.num * r2.don;
	int32_t don = r1.don * r2.num;
	rational_set(r, num, don);
}

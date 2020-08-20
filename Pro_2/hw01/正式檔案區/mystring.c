#include "mystring.h"


//比較c字串中，是否在s中皆存在，若是則回傳1，否則回傳0
int32_t mystrcmp(const char *s, const char *c){
	int32_t count = 0;
	while (*(c + count) !='\0'){
		if (*(s+count) =='\0') return 0;
		if (*(s+count) != *(c+count)) return 0;
		count +=1;
	}
	return 1;
}

//直接往後找 對應字元，若找到直接回傳
//沒找到就回傳NULL的指標
char *mystrchr(const char *s, int32_t c){
	int32_t count = 0 ;
	while (*(s+count) != '\0'){
		//必須強制轉型，因是指標+int
		if (*(s+count)==c) return (char *) s+count; 
		count +=1;
	}
	//當c為'\0'時，查找指向*s的最終位址即可
	if (c==0) return (char *) s+count;
	return NULL;
}

//依然直接往後找對應字元，但一數字不斷紀錄此時的指標
//一直往後找，找到就替換掉先前找到的位置
//如果到結尾了，自動就能取到最後一個對應字元的位置
char *mystrrchr(const char *s, int32_t c){
	int32_t count = 0 ;
	int32_t index = -1;
	while (*(s+count) != '\0'){
		if (*(s+count)==c) index = count;
		count +=1;
	}
	//如果找到，就回傳該指標，沒找到就回傳NULL[同strrchr回傳值]
	if (index !=-1) return (char *) s+index;
	if (c==0) return (char *) s+count;
	
	return NULL;
}

//strspn 中第一個參數是掃描字串，第二個則是有點像字串集合的概念
//當我們在第一個參數開始往後掃時，每看到一個字元
//在第二個字串中只要"存在"這個字元，就等於通過，就可以繼續往下掃
//反之，若是"不存在"則回傳"目前所到的長度"，若超出第一個字串的長度
//則回傳遞一個字串的長度
//因此我們很簡單的 利用 mystrchr 將第二個字串當成字串
//第一個字串中所指到的位置，當作想找到的字元，若沒找到就回傳長度
//就可以很簡單完成此題
size_t mystrspn(const char *s, const char *accept){
	int32_t count = 0;	
	while (*(s+count) != '\0'){		//第一個字串掃完還沒異常就回傳長度
		//若在第二個字串中不存在該字元，就跳出並回傳長度
		if (mystrchr((char *) accept, *(s+count)) == NULL) return count;
		count+=1;
	}
	return count;
}

//跟mystrspn稍稍不一樣，只要在第二個字串中"不存在"這個字元，就pass往下掃
//直到有"存在"的字元或到達字串尾巴，即告結束
size_t mystrcspn(const char *s, const char *reject){
	int32_t count = 0;
	while (*(s+count) != '\0'){
		//也因此，只要將'=='改為'!='即可
		if (mystrchr((char *) reject, *(s+count)) != NULL) return count;
		count+=1;
	}
	return count;
}

//有點像*mystrspn，不過掃描s時
//在accept中若找到符合的字元，則回傳s目前所在位置的"位置"
//若整個都沒找到則回傳NULL
char *mystrpbrk(const char*s, const char *accept){
	int32_t count = 0;
	while (*(s+count)!='\0'){
		if (mystrchr((char *) accept, *(s+count))!=NULL){
			//回傳指標
			return (char *) s+count;
		}
		count +=1;
	}
	//沒找到回傳NULL
	return NULL;
}



//若needle沒字串，則回傳haystack的最開頭位置
//直接haystack一直往後找，每次都用mystrcmp去檢查符合不符合
//因為在此運算時間沒有太大的重要性，因此沒有將時間壓縮
char *mystrstr(const char *haystack, const char *needle){
	if (*needle =='\0') return (char *) haystack;

	int32_t count = 0;

	while (*(haystack+count)!='\0'){
		if (mystrcmp((haystack+count), needle) == 1) return (char *)(haystack+count); 
		count +=1;
	}
	//沒找到就回傳NULL
	return NULL;
}

//分割字元
char *mystrtok(char *str, const char *delim){
	char *tp;

	//因為str掃過第一次找到後是NULL
	//利用static紀錄
	static char *backtok = NULL;

	if (str == NULL){
		str = backtok;
		//看上次存的backtok，如果已經到最底沒找到回傳NULL
		if (backtok == NULL) return NULL;
	}else{
		//還沒找過，從str中找delim第一次出現的所需長度
		//再疊加在str上
		str += strspn(str,delim);
	}

	tp = strpbrk(str, delim);
	//(找到分割字元，將此位置弄成\0，再往後一格)
	if (tp != NULL){
		*tp = '\0';
		backtok = tp + 1;
	//位置不存在就NULL
	}else{
		backtok = NULL;
	}

	return str;
}




#include <stdint.h>
#include "mystring.h"
#include <stdio.h>

//讀掉空白
void readspace(){
	char s= getchar();
	while (s==' '){
		if (s==EOF || s=='\n') return;
		s = getchar();
	}
	//讀到正常的東西，就把他吐回buffer
	ungetc(s, stdin);
	return;
}

//recursion for the hw0103
//字串、pattern都應該只包含小寫字母[根據題意]
int32_t res(char *pat, char *str, int32_t indexp, int32_t indexs){
	//pattern有空白，就跳到下一個
	//pattern根據題意，不應該包含空白，而僅以小寫組成才對
	if (*(pat+indexp) == ' ') return res (pat, str, indexp+1, indexs);
	//如果讀到pattern的底了，代表符合條件
	if (*(pat+indexp+1) == '\0'){
		printf("%s ", str);
		return 1;

	//原始字串讀完，或讀取到空白，而不符合上述條件
	//代表不符合pattern
	}else if (*(str+indexs) == '\0' || *(str+indexs) == ' ') return -1;

	//問號就無條件往下一個state
	if (*(pat+indexp) == '?'){
		return res(pat, str, indexp+1, indexs+1);
	//如果pattern和字串一樣就往下一個state
	}else if (*(str+indexs) == *(pat+indexp)){
		return res(pat, str, indexp+1, indexs+1);

	}else if (*(pat+indexp) == '*'){
		//兩個以上的*連在一起，相當於一個*
		if (*(pat+indexp+1)=='*') return res(pat, str, indexp+1, indexs);
		//可以將*當作一個?
		if (res(pat, str, indexp+1, indexs+1) == 1) return 1;
		//可以將*當作好幾個字元
		if (res(pat, str, indexp, indexs+1) == 1) return 1;
		//也可以將*當作空白
		if (res(pat, str, indexp+1, indexs) == 1) return 1;
		return -1;
	//除此以外就是Not Found囉
	}else return -1;

}; 

//讀入字串
void readstr(char *str){
	int32_t count  = 0 ;
	char s = getchar();
	while (s!=EOF && s!='\n'){
		*(str+count) = s;
		count +=1;
		s = getchar();
	}
}

int main(){

	char pat[999999];
	char str[999999];

	printf("Please enter the pattern: ");
	readspace();
	readstr(pat);
	printf("Please enter the string: ");
	readstr(str);
	printf("Result: ");

	int32_t count = 0;
	char *spli = " ";
	char *ptr = mystrtok(str,spli);

	//用strtok切割空白
	while (ptr != NULL){
		res(pat,ptr,0,0);
		ptr = mystrtok(NULL,spli);
	}

	return 0;
}

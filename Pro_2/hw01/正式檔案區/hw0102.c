#include <stdio.h>
#include <stdint.h>

//若輸入有問題，馬上把後面全部讀掉，直到換行、EOF
void readend(){
	char s;
	s = getchar();
	while (1){
		if (s=='\n' || s==EOF) break;
		s = getchar();
	}
}

//究竟輸入是否為"十六進制"的數字
//是則回傳1，為冒號則回傳2，其餘回傳0
int32_t verify(char p){
	if (p >= 'A' && p <= 'F') return 1;
	if (p >= 'a' && p <= 'f') return 1;
	if (p >= '0' && p <= '9') return 1;
	if (p == ':') return 2;
	return 0;
}

int main(){
	//str拿來暫存 可行的輸入
	char str[25];
	//s拿來先檢查輸入
	char s;

	//考慮使用者輸入空白也要能夠接受
	//且輸入有可能非常大，故使用getchar處理
	printf("Please enter the string: ");

	//count紀錄出現幾次冒號
	//num_count紀錄目前在讀冒號後第幾個十六位數
	//num_count長度應只能為2
	int32_t count = 0;
	int32_t num_count = 0, temp = 0;

	while (1){
		s = getchar();
		if (s==' ') continue;

		if (s==EOF || s=='\n') temp =3;
		else temp = verify(s);
		
		//輸入為合法數字，長度正確就存進去
		if (temp == 1 && count <=5 && num_count <=2){
			str[count*3+num_count] = s;
			num_count+=1;
		//輸入為冒號，且長度為2(十六進位)代表合法
		//繼續累進，並把str內:處改-
		}else if (count <=5 && num_count ==2 && temp ==2){
			str[count*3+num_count] = '-';
			count +=1;
			num_count = 0;
		//如果出現過五個冒號，且輸入至最底了，就輸出
		}else if (count ==5 && temp ==3){
			str[18] = '\0';
			printf("%s\n", str);
			break;
		}else{
		//還是不行，就把後面的讀光
			readend();
			printf("invalid\n");
			break;
		}
	}

	return 0;
}

#include "rational.h"
//rational =>不考慮虛數


//把剩下的讀掉
void readend(){
	char s = '1';
	while (s!=EOF && s!='\n') s = getchar();
}

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

//讀取運算符號
int32_t readsign(char *p){
	readspace();
	char s = getchar();

	//讀到最後了
	if (s==EOF || s=='\n') return 0;
	else if (s=='+' || s=='-' || s=='*' || s=='/'){
		*p = s;
		//讀取成功
		return 1;

	}else return -1; //錯誤

	return 0;
}

//讀取分數
int32_t readfraction(struct rational *r){
	//先把空白讀掉，之後讀第一個非空白字元
	readspace();
	char s = getchar();
	char str[10000];
	//先檢查有沒有左括號，沒有馬上就抓包他是不合法的!
	if (s =='('){
		int32_t count = 0;
		//讀到之後，再把空白處理掉
		readspace();
		s = getchar();
		//如果不是數字或-號，就不合法，那麼就直接讀掉全部
		if (!(s>='0' && s<='9') || s=='-'){
			readend();
			return -1;
		}
		int32_t check = 0;

		//開始一直往後跑，直到讀取到右括號
		while (1){
			readspace();
			if (s==EOF || s=='\n') return -1;
			else if (s==')'){
				while (count !=0){
					ungetc(str[--count],stdin);
				}
				break;
			}else if (s==',' && check == 0){
				readspace();
				check =1;
				str[count++] = s;
				readspace();
				s = getchar();
				str[count++] = s;
			}else if (s>='0' && s<='9') str[count++] = s;
			else{
				//以上都不是，那當然也是不合法的，例如虛數i，非rational也是不合法
				readend();
				return -1;
			}
			readspace();
			s = getchar();
		}
		scanf("%d", &(r->num));
		s = getchar();
		if (s !=',') return -1;
		scanf("%d", &(r->don));

	}else return -1;

}

//將分數的struct由no到end一律往左移動一位
void shift_rational(struct rational nu[], int32_t no, int32_t end, int32_t *nb){
	for (int32_t i = no ; i < end; i++){
		rational_set(&nu[i], nu[i+1].num, nu[i+1].don);
	}
	*nb -=1;
}

//將符號array一律往左移一位
void shift_sign(char *r, int32_t no, int32_t end){
	for (int32_t i = no; i <end; i++){
		*(r+i) = *(r+i+1);
	}
}

//進行四則運算
void operation(struct rational nu[], char *r, int32_t *nb){
	int32_t i = 0;
	//乘除優先 所以先讀
	while (i <= *nb){
		if (*(r+i)=='*' || *(r+i)=='/'){
			struct rational c;
			//單純用自己寫的標頭檔
			if (*(r+i) =='*') rational_mul(&c, nu[i], nu[i+1]);

			else if (*(r+i) =='/') rational_div(&c, nu[i], nu[i+1]);

			rational_set(&nu[i], c.num, c.don);
			shift_rational(nu, i+1, *nb, nb);
			shift_sign((r+i), i, *nb); 

			if (i==*nb) break;
			i-=1;
		}
		if (*nb==0) break;
		i+=1;
	}
	i = 0;

	//再跑一次加減的
	while (i <= *nb){
		if (*(r+i)=='+' || *(r+i) =='-'){
			struct rational c;
			if (*(r+i) == '+') rational_add(&c, nu[i], nu[i+1]);

			else if (*(r+i) =='-') rational_sub(&c, nu[i], nu[i+1]);
			
			rational_set(&nu[i], c.num, c.don);
			shift_rational(nu, i+1, *nb, nb);
			shift_sign((r+i), i, *nb);
			if (i==*nb) break;
			//運算後存在原本位置，所以運算位置並不會動
			//但如果扣一的話，我要注意是不是已經到最後了
			//如果已經到最後卻沒有break而是扣一，我會額外多做一次運算
			i-=1;
		}
		if (*nb==0) break;
		i+=1;
	}
}

int main(){

    struct rational nu[99999];
	char oper[99999];
	
	printf("Please enter the equation: ");

	//用nob去紀錄目前存到的位置到哪
	int32_t nob = 0;
	while (1){
		int32_t temp = readfraction(&(nu[nob]));

		//檢查輸入是否正確
		//不合法就提示一下
		if (temp== -1){
			printf("input error!\n");
			break;
		}
		int32_t temp_sign = readsign(&(oper[nob]));

		//如果讀到底了，就開始運算，最後break;
		if (temp_sign ==0){
			operation(nu, oper, &nob);
			printf("(%d,%d)\n", nu[0].num, nu[0].don);
			break;
		//不合法還是印不合法
		}else if (temp_sign == -1){
			printf("input error!\n");
			break;
		}
		nob +=1;
	}

	return 0;
}

#include <stdio.h>
#include <stdint.h>

int main(){

	int32_t number = 0;
	scanf("%d", &number);

	//可解釋了
	int32_t bit = 1;
	bit = bit << 31;
	printf("%02X\n", bit);
	printf("%d\n",bit);
	bit = bit >> 1;
	printf("%02X\n", bit);
	printf("%d\n",bit);

	for (int32_t i = 0 ; i < 32; i++){
		if (bit & number)
			printf("1");
		else
			printf("0");
		bit = bit >>1;
	}

	return 0;
}

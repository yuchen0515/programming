#include <stdio.h>
#include <stdint.h>

int main(){
	int32_t mask = 1 << 1, mask2;
	int32_t save= 216;
	int32_t tp = 3;

	for (int32_t i = 0 ; i < 2 ; i++){
		mask2 = (tp & mask);
		mask >>= 1;
		save |= mask2;
		printf("%d\n", mask2);
	}
	puts("");
	printf("%d\n", save);


	return 0;
}

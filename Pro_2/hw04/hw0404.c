#include <stdio.h>
#include <stdint.h>
#define FOR_EACH(var, i, j) for(int32_t var = i ; var < j; var++)
#define FOR_EACH_STEP(var, i, j, step) for(int32_t var = i ; var < j; var+=step)
#define SUM_OF_ARRAY(array, i, j, sum) \
	int32_t sum = 0;	\
	for(int32_t p = i ; p < j ; p++){\
	sum += array[p];\
}

int main(){

	int32_t x[] = {1,2,3,4,5,6,7,8,9,10};
	int32_t n = 10;

	//單層迴圈, STEP == 1
	printf("-----單層迴圈, i = 0 ~ 10, i++ -----\n");
	FOR_EACH(i, 0, 10){
		printf("%d ", i);
	}
	puts("\n\n");

	//單層迴圈, SETP使用者自訂
	printf("-----單層迴圈, i = 0 ~ 10, i+=2 -----\n");
	int32_t step = 2;
	FOR_EACH_STEP(i, 0, 10, 2){
		printf("%d ", i);
	}
	puts("\n\n");

	//陣列加總
	printf("-----陣列加總, sum = x[0] + ... + x[10] -----\n");
	SUM_OF_ARRAY(x, 0, 10, sum);
	printf("%d\n", sum);
	puts("\n");


	//巢狀迴圈, STEP == 1
	printf("-----巢狀迴圈, 九九乘法表_example -----\n");
	FOR_EACH(i, 1, 11){
		FOR_EACH(j, 1, 11){
			printf("%d * %d = %d\t", i, j, i*j);
			if (j == 5) puts("");
		}
		puts("");
	}

	
	return 0;
}

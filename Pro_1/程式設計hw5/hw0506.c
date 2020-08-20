#include <stdio.h>
#include <stdint.h>

int main(){

	uint8_t array[5] = {0};
	
	//uint8_t array[8] = {0};

	//for (int32_t i = 0 ; i<5 ;i++){
	for(int32_t i=4; i>=0 ;i--){
		printf("Please enter a number: ");
		scanf("%u", &(array[i]));
	}
	for (int32_t i = 0 ; i<5 ;i++){
		printf("%u ", array[i]);
	}
	printf("\n");
	/*
	uint8_t* ptr = &array[4];
	for(int32_t i=0; i<4;i++){
		ptr++;
		printf("%d\n",*ptr);
	}
	*/

	return 0;
}

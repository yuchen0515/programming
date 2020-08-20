#include <stdio.h>
#include <stdint.h>
#include "zeroes.h"


int32_t compare (int32_t a, int32_t b){
	if (a==0 && b!=0) return 1;
	return 0;
}


int main(){

	int32_t len_arr = sizeof(array)/sizeof(int32_t);

	int32_t *first = array;

	if (len_arr>1){
		for (int32_t i = 0 ; i < len_arr; i++){
			for	(int32_t j = 1 ; j < len_arr-i; j++){
				if (compare(*(first+j-1), *(first+j))){
					*(first+j-1) ^= *(first+j);			
					*(first+j) ^= *(first+j-1);
					*(first+j-1) ^= *(first+j);			
				}
			}
		}

	}
	for (int32_t i = 0 ; i < len_arr; i++){
		printf("%d ", *(first+i));
	}
	puts("");


}

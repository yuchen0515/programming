#include <stdio.h>
#include <stdint.h>
#include "readfile.h"

int main(){
	while (1){
		printf("Please enter the mbox file: ");
		printf("1) Who commits most?\n");
		printf("2) Who commits most in 20:00-24:00?\n");
		printf("3) What New revision change the most files?\n");
		printf("4) New revision --> user\n");
		printf("5) Exit.\n");
		printf("Your Choice:");
		int32_t temp = 0;
		scanf("%d", &temp);
		if (temp ==1){

		}else if (temp ==2){

		}else if (temp ==3){
		}else if (temp ==4){
		}else if (temp ==5){
		}else{
			printf("Input error!\n");
		}
	}
	

	return 0;
}

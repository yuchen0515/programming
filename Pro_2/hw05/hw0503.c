#include <stdio.h>
#include <stdint.h>
#include "hw0503_header.h"

void test(){
	debug_print(DEBUG_LEVEL_ERROR,"This is a LEVEL_ERROR message %d.\n", 1);
}


int main(){

	printf("Hello, user!\n\n");
	printf("-------------------DEBUG MESSAGE OUTPUT-----------------------\n\n");
	//0=NONE
	debug_print(0,"This is a LEVEL_NONE message %d.\n", 0);
	//1=ERROR
	debug_print(1,"This is a LEVEL_ERROR message %d.\n", 1);
	//2=INFO
	debug_print(2,"This is a LEVEL_INFO message %d.\n", 2);
	//3=VERBOSE 
	debug_print(3,"This is a LEVEL_VERBOSE message %d.\n", 3);
	//4=VVERBOSE
	debug_print(4,"This is a LEVEL_VVERBOSE message %d.\n", 4);
	printf("\n\n-----------------------REVERSE OUTPUT-------------------------\n\n");

	debug_print(DEBUG_LEVEL_VVERBOSE,"This is a LEVEL_VVERBOSE message %d.\n", 4);
	debug_print(DEBUG_LEVEL_VERBOSE,"This is a LEVEL_VERBOSE message %d.\n", 3);
	debug_print(DEBUG_LEVEL_INFO,"This is a LEVEL_INFO message %d.\n", 2);
	test();
	debug_print(DEBUG_LEVEL_NONE,"This is a LEVEL_NONE message %d.\n", 0);
	printf("\n\n--------------------------------------------------------------\n\n");
	printf("All message is output already above.\n");


	return 0;
}

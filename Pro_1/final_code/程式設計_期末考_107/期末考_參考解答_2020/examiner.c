#include "examiner.h"

int32_t secret[4] = {0};

void setup(){
	for (int32_t i = 0 ; i < 4 ; i++){
		secret[i] = rand()%4;
	}
}

int32_t check( int32_t guess[4], int32_t *bull, int32_t *cow){
	*bull = 0;
	*cow = 0;
	int32_t copy[4] ={1};
	int32_t index = 0;
	for (int32_t i = 0 ; i<4; i++){
		if (guess[i] == secret[i]){
			*bull+=1;
			copy[i] = 0;
		}else{
			for (int32_t j = i+1; j<4; j++){
				if (guess[i]==secret[j] && copy[j]){
					*cow +=1;
					copy[j] = 0;
				}
			}
		}
	}

	if (*bull==4) return 1;
	else if (*bull + *cow > 0) return -1;
	else return 0;
}

#include "player.h"
#include "examiner.h"

int32_t gen_guess(int32_t guess[4], int32_t bull, int32_t cow ){

	int32_t bul = bull;
	int32_t temp = check(guess, &bull, &cow);
	if (temp==1)	return 1;
	else{
		int32_t i = rand()%4;
		//for (int32_t i = 0; i < 4 ; i++){
			int32_t tep= guess[i];
			for (int32_t j = 1; j < 10; j++){
				guess[i] = j;
				int32_t tepp = check(guess, &bull, &cow);
				if (bull > bul){
					bul++;
					break; 
				}else{
					guess[i] = tep;
				}
			}

		//}
	}
	temp = check(guess, &bull, &cow);
	return temp;
}

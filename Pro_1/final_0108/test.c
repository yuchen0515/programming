#include <stdio.h>
#include <stdint.h>

//#include "examiner.h"

int check(int *test_guess, int *bull, int *cow)
{
    for(int i = 0; i < 4; i++)
    {
        if(test_guess[i] < 0 || test_guess[i] > 9)
        {
            return -1;
        }
    }
    
    int number[10] = {};
    for(int i = 0; i < 4; i++)
    {
        number[test_guess[i]] += 1;
    }
    for(int i = 0; i < 10; i ++)
    {
        if(number[i] > 1)
        {
            return -1;
        }
    }
    return 1;
}

int main()
{
    int32_t result = 0;
    int bull = 0, cow = 0;
    
    int32_t test_guess1[4] = {1, 1, 1, 1};
    result = check(test_guess1, &bull, &cow);
    
    if(result == 1)
    {
        printf("invalid checking");
    }
    else if(result == -1)
    {
        printf("valid checking\n");
    }
    
    int32_t test_guess2[4] = {-1, 0, 1, 2};
    result = check(test_guess2, &bull, &cow);
    
    if(result == 1)
    {
        printf("invalid checking\n");
    }
    else if(result == -1)
    {
        printf("valid checking\n");
    }
    
    int32_t test_guess3[4] = {11, 1, 2, 3};
    result = check(test_guess3, &bull, &cow);
    
    if(result == 1)
    {
        printf("invalid checking\n");
    }
    else if(result == -1)
    {
        printf("valid checking\n");
    }
}

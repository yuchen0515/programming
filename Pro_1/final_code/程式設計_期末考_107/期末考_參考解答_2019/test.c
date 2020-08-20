#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "final.h"

/*
* I will give you some "simple" test case here.
* However, TA will use more test cases to test your function.
*/ 

int main()
{
    // Problem 01: Matrix Operation

    int32_t matrix01[9] = { 2, 5, 17, -5, 3, 1, 1, 8, -15};
    int32_t matrix02[9] = { 5, 2, -5, 17, 3, 8, 1, 1, -15};
    int32_t output[9] = {0};
    int32_t answerAdd[9] = { 7, 7, 12, 12, 6, 9, 2, 9, -30};
    int32_t answerSub[9] = { -3, 3, 22, -22, 0, -7, 0, 7, 0};
    int32_t answerMul[9] = { 112, 36, -225, 27, 0, 34, 126, 11, 284};
    int32_t answerTp[9] = { 2, -5, 1, 5, 3, 8, 17, 1, -15};
	/*
    int32_t matrix01[4] = { 1, 1, 1, 1 };
    int32_t matrix02[4] = { 1, 0, 0, 1 };
    int32_t output[4] = {0};
    int32_t answerAdd[4] = { 2, 1, 1, 2 };
    int32_t answerSub[4] = { 0, 1, 1, 0 };
    int32_t answerMul[4] = { 1, 1, 1, 1 };
    int32_t answerTp[4] = { 1, 1, 1, 1 };
	*/
    
    addMatrix( output, matrix01, matrix02, 3, 3 );
    
    if( memcmp( output, answerAdd, sizeof( int32_t ) * 9 ) == 0 )
    {
        printf( "Problem 01-01 is OK.\n" );
    }
    else
    {
        printf( "Problem 01-01 fails.\n" );
    }
    
    subMatrix( output, matrix01, matrix02, 3, 3 );
    
    if( memcmp( output, answerSub, sizeof( int32_t ) * 9 ) == 0 )
    {
        printf( "Problem 01-02 is OK.\n" );
    }
    else
    {
        printf( "Problem 01-02 fails.\n" );
    }
    
    mulMatrix( output, matrix01, 3, 3, matrix02, 3, 3 );
    
    if( memcmp( output, answerMul, sizeof( int32_t ) * 9 ) == 0 )
    {
        printf( "Problem 01-03 is OK.\n" );
    }
    else
    {
        printf( "Problem 01-03 fails.\n" );
    }
    
    tpMatrix ( output, matrix01, 3, 3 );
    
    if( memcmp( output, answerTp, sizeof( int32_t ) * 9 ) == 0 )
    {
        printf( "Problem 01-04 is OK.\n" );
    }
    else
    {
        printf( "Problem 01-04 fails.\n" );
    }
    
    // Problem 02: Sorting Two Arrays
    
    int32_t array01[3] = {13, 18, 52};
    int32_t array02[5] = {26, 10, 39, 42, 15};
    int32_t arrayAns01[8] = { 52, 42, 39, 26, 18, 15, 13, 10};
    int32_t arrayAns02[8] = { 10, 13, 15, 18, 26, 39, 42, 52};
    int32_t arrayAns03[8] = { 52, 39, 26, 13, 42, 18, 15, 10};
    int32_t output2[8] = {0};
	/*
    int32_t array01[1] = {13};
    int32_t array02[1] = {14};
    int32_t arrayAns01[2] = { 14, 13 };
    int32_t arrayAns02[2] = { 13, 14 };
    int32_t arrayAns03[2] = { 13, 14 };
    int32_t output2[2] = {0};
	*/
    
    sortTwoArray01( output2, array01, 3, array02, 5 );
    
    if( memcmp( output2, arrayAns01, sizeof( int32_t ) * 8 ) == 0 )
    {
        printf( "Problem 02-01 is OK.\n" );
    }
    else
    {
        printf( "Problem 02-01 fails.\n" );
    } 
    
    int32_t *pOutput = NULL;
    
    sortTwoArray02( &pOutput, array01, 3, array02, 5 );
    
    if( pOutput == NULL )
    {
        printf( "Problem 02-02 fails.\n" );
    }
    else if( memcmp( pOutput, arrayAns02, sizeof( int32_t ) * 8 ) == 0 )
    {
        printf( "Problem 02-02 is OK.\n" );
    }
    else
    {
        printf( "Problem 02-02 fails.\n" );
    }
    
    sortTwoArray03( output2, array01, 3, array02, 5 );
    
    if( memcmp( output2, arrayAns03, sizeof( int32_t ) * 8 ) == 0 )
    {
        printf( "Problem 02-03 is OK.\n" );
    }
    else
    {
        printf( "Problem 02-03 fails.\n" );
    } 
    
    // Problem 03: String to Number
    
    uint32_t ans0301_01 = 0;
    uint64_t ans0302_01 = 0;
    
    myAtoi( "25556", &ans0301_01 );
    
    if( ans0301_01 == 25556 )
    {
        printf( "Problem 03-01 is OK.\n" );
    }
    else
    {
        printf( "Problem 03-01 fails.\n" );
    }
    
    myAtol( "12345678910", &ans0302_01 );
    
    if( ans0302_01 == 12345678910 )
    {
        printf( "Problem 03-02 is OK.\n" );
    }
    else
    {
        printf( "Problem 03-02 fails.\n" );
    }
    
    uint32_t output3[16] = {0};
    uint32_t answer3[16] = {0};
    //answer3[0] = 255;
   	answer3[0] = 0; 
	answer3[1] = 2;
    //myAto512( "255", output3 );
    myAto512( "8589934592", output3 );
    
    if( memcmp( output3, answer3, sizeof( uint32_t ) * 16 ) == 0 )
    {
        printf( "Problem 03-03 is OK.\n" );
    }
    else
    {
        printf( "Problem 03-03 fails.\n" );
    } 
    
    // Problem 04: Sudoku Solver
    
    int32_t puzzle[9][9] = { { 5, 3, 0, 0, 7, 0, 0, 0, 0 },
                             { 6, 0, 0, 1, 9, 5, 0, 0, 0 },   
                             { 0, 9, 8, 0, 0, 0, 0, 6, 0 },
     						 { 8, 0, 0, 0, 6, 0, 0, 0, 3 },
     						 { 4, 0, 0, 8, 0, 3, 0, 0, 1 },
                             { 7, 0, 0, 0, 2, 0, 0, 0, 6 },   
                             { 0, 6, 0, 0, 0, 0, 2, 8, 0 },
     						 { 0, 0, 0, 4, 1, 9, 0, 0, 5 },
     						 { 0, 0, 0, 0, 8, 0, 0, 7, 9 } };
    
    int32_t puzzleAnswer[9][9] = { { 5, 3, 4, 6, 7, 8, 9, 1, 2 },
                             { 6, 7, 2, 1, 9, 5, 3, 4, 8 },   
                             { 1, 9, 8, 3, 4, 2, 5, 6, 7 },
     						 { 8, 5, 9, 7, 6, 1, 4, 2, 3 },
     						 { 4, 2, 6, 8, 5, 3, 7, 9, 1 },
                             { 7, 1, 3, 9, 2, 4, 8, 5, 6 },   
                             { 9, 6, 1, 5, 3, 7, 2, 8, 4 },
     						 { 2, 8, 7, 4, 1, 9, 6, 3, 5 },
     						 { 3, 4, 5, 2, 8, 6, 1, 7, 9 } };
    
    int32_t temp = playSudoku( puzzle );
    
    if( memcmp( puzzle, puzzleAnswer, sizeof( int32_t ) * 81 ) == 0 )
    {
        printf( "Problem 04 is OK.\n" );
    }
    else
    {
        printf( "Problem 04 fails.\n" );
    } 
    
    // Bonus: Binary Complement
	int32_t Binary_input = 229;
	int32_t ans0501 = binComplement(Binary_input);

	if (ans0501 == 27){
        printf( "Problem 05 is OK.\n" );

	}else{
        printf( "Problem 05 fails.\n" );
	}
    
    return 0;
}



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

    int32_t matrix01[4] = { 1, 1, 1, 1 };
    int32_t matrix02[4] = { 1, 0, 0, 1 };
    int32_t output[4] = {0};
    int32_t answerAdd[4] = { 2, 1, 1, 2 };
    int32_t answerSub[4] = { 0, 1, 1, 0 };
    int32_t answerMul[4] = { 1, 1, 1, 1 };
    int32_t answerTp[4] = { 1, 1, 1, 1 };
    
    addMatrix( output, matrix01, matrix02, 2, 2 );
    
    if( memcmp( output, answerAdd, sizeof( int32_t ) * 4 ) == 0 )
    {
        printf( "Problem 01-01 is OK.\n" );
    }
    else
    {
        printf( "Problem 01-01 fails.\n" );
    }
    
    subMatrix( output, matrix01, matrix02, 2, 2 );
    
    if( memcmp( output, answerSub, sizeof( int32_t ) * 4 ) == 0 )
    {
        printf( "Problem 01-02 is OK.\n" );
    }
    else
    {
        printf( "Problem 01-02 fails.\n" );
    }
    
    mulMatrix( output, matrix01, 2, 2, matrix02, 2, 2 );
    
    if( memcmp( output, answerMul, sizeof( int32_t ) * 4 ) == 0 )
    {
        printf( "Problem 01-03 is OK.\n" );
    }
    else
    {
        printf( "Problem 01-03 fails.\n" );
    }
    
    tpMatrix ( output, matrix01, 2, 2 );
    
    if( memcmp( output, answerMul, sizeof( int32_t ) * 4 ) == 0 )
    {
        printf( "Problem 01-04 is OK.\n" );
    }
    else
    {
        printf( "Problem 01-04 fails.\n" );
    }
    
    // Problem 02: Sorting Two Arrays
    
    int32_t array01[1] = {13};
    int32_t array02[1] = {14};
    int32_t arrayAns01[2] = { 14, 13 };
    int32_t arrayAns02[2] = { 13, 14 };
    int32_t arrayAns03[2] = { 13, 14 };
    int32_t output2[2] = {0};
    
    sortTwoArray01( output2, array01, 1, array02, 1 );
    
    if( memcmp( output2, arrayAns01, sizeof( int32_t ) * 2 ) == 0 )
    {
        printf( "Problem 02-01 is OK.\n" );
    }
    else
    {
        printf( "Problem 02-01 fails.\n" );
    } 
    
    int32_t *pOutput = NULL;
    
    sortTwoArray02( &pOutput, array01, 1, array02, 1 );
    
    if( pOutput == NULL )
    {
        printf( "Problem 02-02 fails.\n" );
    }
    else if( memcmp( pOutput, arrayAns02, sizeof( int32_t ) * 2 ) == 0 )
    {
        printf( "Problem 02-02 is OK.\n" );
    }
    else
    {
        printf( "Problem 02-02 fails.\n" );
    }
    
    sortTwoArray03( output2, array01, 1, array02, 1 );
    
    if( memcmp( output2, arrayAns03, sizeof( int32_t ) * 2 ) == 0 )
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
    
    myAtoi( "255", &ans0301_01 );
    
    if( ans0301_01 == 255 )
    {
        printf( "Problem 03-01 is OK.\n" );
    }
    else
    {
        printf( "Problem 03-01 fails.\n" );
    }
    
    myAtol( "1234567", &ans0302_01 );
    
    if( ans0302_01 == 1234567 )
    {
        printf( "Problem 03-02 is OK.\n" );
    }
    else
    {
        printf( "Problem 03-02 fails.\n" );
    }
    
    uint32_t output3[16] = {0};
    uint32_t answer3[16] = {0};
    answer3[0] = 255;
    
    myAto512( "255", output3 );
    
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
    
    playSudoku( puzzle );
    
    if( memcmp( puzzle, puzzleAnswer, sizeof( int32_t ) * 81 ) == 0 )
    {
        printf( "Problem 04 is OK.\n" );
    }
    else
    {
        printf( "Problem 04 fails.\n" );
    } 
    
    // Bonus: Binary Complement
    
    return 0;
}



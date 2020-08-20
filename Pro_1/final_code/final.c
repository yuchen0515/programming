#include "final.h"

// Problem 01: Matrix Operation

void addMatrix( int32_t output[], int32_t oprand1[], int32_t operand2[], int32_t row, int32_t column )
{
    return;
}

void subMatrix( int32_t output[], int32_t oprand1[], int32_t operand2[], int32_t row, int32_t column )
{
    return;
}

int32_t mulMatrix( int32_t output[], int32_t oprand1[], int32_t row1, int32_t column1, int32_t operand2[], int32_t row2, int32_t column2 )
{
    return 0;
}

void tpMatrix ( int32_t output[], int32_t oprand1[], int32_t row, int32_t column )
{
    return;
}

// Problem 02: Sorting Two Arrays

void sortTwoArray01( int32_t output[], int32_t array01[], int32_t size01, int32_t array02[], int32_t size02 )
{
    return;
}

void sortTwoArray02( int32_t **ppOutput, int32_t array01[], int32_t size01, int32_t array02[], int32_t size02 )
{
    return;
}

void sortTwoArray03( int32_t output[], int32_t array01[], int32_t size01, int32_t array02[], int32_t size02 )
{
    return;
}

// Problem 03: String to Number

void myAtoi( char *pStr, uint32_t *pResult )
{
    return;
}

void myAtol( char *pStr, uint64_t *pResult )
{
    return;
}

// Binus: If the value of the input string isover 512 bits, return -1.
int32_t myAto512( char *pStr, uint32_t result[16] )
{
    return 0;
} 

// Problem 04: Sudoku Solver 

static int32_t isValid( int32_t number, int32_t puzzle[9][9], int32_t row, int32_t column ) 
{
    int32_t sectorRow = 3 * ( row/3 );
    int32_t sectorCol = 3 * ( column/3 );
    int32_t row1 = ( row + 2 )%3;
    int32_t row2 = ( row + 4 )%3;
    int32_t col1 = ( column + 2 ) % 3;
    int32_t col2 = ( column + 4 ) % 3;
 
    /* Check for the value in the given row and column */
    for ( int32_t i = 0; i < 9; i++ ) 
    {
        if ( puzzle[i][column] == number ) return 0;
        if ( puzzle[row][i] == number ) return 0;
    }
 
    /* Check the remaining four spaces in this sector */
    if( puzzle[row1+sectorRow][col1+sectorCol] == number ) return 0;
    if( puzzle[row2+sectorRow][col1+sectorCol] == number ) return 0;
    if( puzzle[row1+sectorRow][col2+sectorCol] == number ) return 0;
    if( puzzle[row2+sectorRow][col2+sectorCol] == number ) return 0;
    return 1;
}

// 0 means fail, 1 means pass
static int32_t sudokuSolver( int32_t puzzle[9][9], int32_t row, int32_t column ) 
{
    
    /*
    * Implement this function here.
    */

    return 0;
}

int32_t playSudoku( int32_t puzzle[9][9] )
{
    /*
    * Hint:
    * You can use the recursive approach.
    * sudokuSolver can be implemented as a recursive function.
    * The template of sudoku is given before this function.
    * If you want to use this approach, uncomment the following line.
    * Of course, you can use your own solution.
    * The recursive way is easy. You should call sudokuSolver( puzzle, m, n+1 ) in sudokuSolver.
    * When n+1 == 9, call sudokuSolver( puzzle, m+1, 0 ) 
    */
    // return sudokuSolver( puzzle, 0, 0 );
    return 0;
}

// Bonus: Binary Complement

int32_t binComplement( int32_t input )
{
    return 0;
}

#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// Problem 01: Matrix Operation

void addMatrix( int32_t output[], int32_t oprand1[], int32_t operand2[], int32_t row, int32_t column );
void subMatrix( int32_t output[], int32_t oprand1[], int32_t operand2[], int32_t row, int32_t column );
int32_t mulMatrix( int32_t output[], int32_t oprand1[], int32_t row1, int32_t column1, int32_t operand2[], int32_t row2, int32_t column2 );
void tpMatrix ( int32_t output[], int32_t oprand1[], int32_t row, int32_t column );

// Problem 02: Sorting Two Arrays

void sortTwoArray01( int32_t output[], int32_t array01[], int32_t size01, int32_t array02[], int32_t size02 );
void sortTwoArray02( int32_t **ppOutput, int32_t array01[], int32_t size01, int32_t array02[], int32_t size02 );
void sortTwoArray03( int32_t output[], int32_t array01[], int32_t size01, int32_t array02[], int32_t size02 );

// Problem 03: String to Number

void myAtoi( char *pStr, uint32_t *pResult );
void myAtol( char *pStr, uint64_t *pResult );
int32_t myAto512( char *pStr, uint32_t result[16] ); 

// Problem 04: Sudoku Solver 

int32_t playSudoku( int32_t puzzle[9][9] );

// Bonus: Binary Complement

int32_t binComplement( int32_t input );

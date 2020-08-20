#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

typedef struct _sMatrix{
	int32_t data;
    struct _sMatrix *col;
    struct _sMatrix *row;
}sMatrix;

sMatrix *allocMatrix( int32_t val ){

    sMatrix *newComer = calloc( 1, sizeof( sMatrix) );
        
    newComer -> data = val;
        
    return newComer;
}

void init_matrix( sMatrix *m, int32_t row_num, int32_t col_num){

	sMatrix *ptr = m;
	ptr -> data = 0;
	ptr -> col = NULL;
	ptr -> row = NULL;

	for (int32_t i = 0 ; i < col_num; i++){
		sMatrix *cptr = allocMatrix(0);
		ptr -> col = cptr;
		cptr -> col = NULL;
		cptr -> row = NULL;

		for (int32_t j = 0 ; j < row_num; j++){
			sMatrix *rptr = allocMatrix(0);
			cptr -> row = rptr;
			rptr -> col = NULL;
			rptr -> row = NULL;

			cptr = cptr -> row;
		}
		
		ptr = ptr -> col;
	}
}


//m[a][b] = val
void set_matrix( sMatrix *m, int32_t a, int32_t b, int32_t val){




}
void free_matrix( sMatrix *m);

void print_matrix( sMatrix *m){

	sMatrix *ptr = m;

	while (ptr -> col){
		ptr = ptr -> col;
		sMatrix *rptr = NULL;
		while (rptr -> row){
			rptr = rptr -> row;
			printf("%d ", rptr->data);
		}
	}

}
/*
   void printCharacter( sCharacter *one ){
   printf( "%04d) ", one -> id );
   printf( "%8s ", one -> name );

   for( int32_t *ptr = &( one -> hp ); ptr <= &( one -> spd ); ptr++ ){
   printf( "%3d ", *ptr );
   }

   printf( "\n" );
   return;
   }
 */

//output = a + b
// return -1 if fail
int32_t add_matrix( sMatrix *output, sMatrix a, sMatrix b);

//output = a * b
// return -1 if fail
int32_t mul_matrix( sMatrix *output, sMatrix a, sMatrix b);

void transpose_matrix( sMatrix *m );

//Calculate the determinant
int32_t det_matrix( sMatrix *m);






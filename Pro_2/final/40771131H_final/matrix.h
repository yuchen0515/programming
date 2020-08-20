#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "linuxlist.h"

typedef struct _sMatrix{
	int32_t data;
    struct list_head row_list;
    struct list_head list;
}sMatrix;


sMatrix *allocMatrix( int32_t val ){

    sMatrix *newComer = calloc( 1, sizeof( sMatrix) );
        
    newComer -> data = val;
        
    return newComer;
}

void init_matrix( sMatrix *m, int32_t row_num, int32_t col_num){

	sMatrix *ptr = m;
	ptr -> data = 0;
	
	for (int32_t i = 0 ; i < col_num ; i++){

		sMatrix *cptr = allocMatrix(0);
		list_add_tail(&(cptr -> list), &(m -> list));

		for (int32_t j = 0 ; j < row_num; j++){
			sMatrix *rptr = allocMatrix(0);
			list_add_tail(&(rptr->row_list), &(cptr -> row_list));
		}
	}
}


//m[a][b] = val
void set_matrix( sMatrix *m, int32_t a, int32_t b, int32_t val){

	if (list_empty(&(m->list))){
		printf("The matrix is empty.\n");
		return;
	}
	
	struct list_head *listptr = NULL;

	int32_t row = 0, col = 0;
	list_for_each(listptr, &(m->list)){
		
		sMatrix *cptr = list_entry(listptr, sMatrix, list);
		struct list_head *rowptr = NULL;

		list_for_each(rowptr, &(cptr->row_list)){
			sMatrix *rptr = list_entry(rowptr, sMatrix, list);
			if (row == a && col == b){
				rptr-> data = val;
			}
			
			col +=1;
		}

		row+=1;
	}



}
void free_matrix( sMatrix *m);

void print_matrix( sMatrix *m){

	if (list_empty(&(m->list))){
		printf("The matrix is empty.\n");
		return;
	}

	
	struct list_head *listptr = NULL;

	/*
	list_for_each(listptr, &(m->list)){
		sMatrix *cptr = list_entry(listptr, sMatrix, list);
		struct list_head *rowptr = NULL;

		printf("%d ", cptr->data);
		list_for_each(rowptr, &(cptr->row_list)){
			sMatrix *rptr = list_entry(rowptr, sMatrix, list);
			printf("%d ", rptr->data);
		}

	}
	*/
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




#include "matrix2.h"

int main(){

	sMatrix m;
    //LIST_HEAD( mat_list_head );    
	init_matrix(&m,  10, 10);
	print_matrix(&m);
    
	/*
    srand( time( 0 ) );
    for( int32_t i = 0 ; i < 1000 ; i++ ){
        sCharacter *newComer = allocCharacter( i + 1 );
        list_add( &( newComer -> list ), &char_list_head );
    }
	*/
    

	/*
    list_for_each( listptr, &char_list_head ){
        sCharacter *cptr = list_entry( listptr, sCharacter, list );
        printCharacter( cptr );
    } 
	*/
    
	/*
    list_for_each_prev( listptr, &mat_list_head )
    {
        sMatrix *cptr = list_entry( listptr, sMatrix, list );
        //printCharacter( cptr );
    } 
	*/

    return 0;
}

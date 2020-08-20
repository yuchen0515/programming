#include <stdio.h>
#include <stdlib.h>

#include "rational.h"

int main()
{
    struct rational a, b, c;
    
    rational_set( &a, 2, 5 );
    rational_set( &b, 7, 5 );
    
    rational_add( &c, a, b );
    rational_print( c );   
    rational_sub( &c, a, b );
    rational_print( c );
    rational_mul( &c, a, b );
    rational_print( c );
    rational_div( &c, a, b );
    rational_print( c );
    
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "rational.h"

int main()
{

    struct rational a, b, c;
    printf("set check: %d\n", rational_set( &a, 1, 0));
    printf("\ninput: 0 -1 1 1\n");
    rational_set( &a, 0, -1 );
    rational_set( &b, 1, 1 );
    rational_add( &c, a, b );
    printf("add:");
    rational_print( c );
    rational_sub( &c, a, b );
    printf("sub:");
    rational_print( c );
    rational_mul( &c, a, b );
    printf("mul:");
    rational_print( c );
    rational_div( &c, a, b );
    printf("div:");
    rational_print( c );

    printf("\ninput: 1 2 2 3\n");
    rational_set( &a, 1, 2 );
    rational_set( &b, 2, 3 );
    rational_add( &c, a, b );
    printf("add:");
    rational_print( c );
    rational_sub( &c, a, b );
    printf("sub:");
    rational_print( c );
    rational_mul( &c, a, b );
    printf("mul:");
    rational_print( c );
    rational_div( &c, a, b );
    printf("div:");
    rational_print( c );

    printf("\ninput: 0 2 0 2\n");
    rational_set( &a, 0, 2 );
    rational_set( &b, 0, 2 );
    rational_add( &c, a, b );
    printf("add:");
    rational_print( c );
    rational_sub( &c, a, b );
    printf("sub:");
    rational_print( c );
    rational_mul( &c, a, b );
    printf("mul:");
    rational_print( c );
    rational_div( &c, a, b );
    printf("div:");
    rational_print( c );
    return 0;
}

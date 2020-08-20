#include <stdio.h>
#include "mystring.h"
#include<stdint.h>
int main()
{
    const char  *str = "";

    int32_t c = 'a';

    printf( "str: \"%s\"\n", str );
    printf( "strchr( str, c ) = %s\n", mystrchr( str, c ) );
    printf( "location is %ld\n", mystrchr( str, c ) - str );
    printf( "strrchr( str, c ) = %s\n", mystrrchr( str, c ) );
    printf( "location is %ld\n", mystrrchr( str, c ) - str );

    printf( "\n" );

    const char  *str2 = "the value of pi is 3.14";
    const char  *accept = "abcdefghijklmnopqrstuvwxyz";
    const char  *reject = "";
    const char  *accept2 = "4";

    printf( "str2: \"%s\"\n", str2 );
    printf( "accept: \"%s\"\n", accept );
    printf( "reject: \"%s\"\n", reject );
    printf( "accept2: \"%s\"\n", accept2 );

    printf( "strspn( str2, accept ) = %ld\n", mystrspn( str2, accept ) );
    printf( "strcspn( str2, reject ) = %ld\n", mystrcspn( str2, reject ) );
    printf( "strpbrk( str2, accept2 ) = %c, which is in %ld\n", *( mystrpbrk( str2, accept2 ) ), mystrpbrk( str2, accept2 ) - str2 );

    printf( "\n" );

    const char  *needle = "d";

    printf( "needle: \"%s\"\n", needle );
    printf( "strstr( str2, needle ): %s\n", mystrstr( str2, needle ) );

    printf( "\n" );

    char    str3[] = "NTNU CSIE-Linux-Ji";
    char    s[] = "--";
    char    *token = mystrtok( str3, s );
    int32_t i = 0;

    while( token != NULL )
    {
        printf( "%d: %s\n", i, token );
        token = mystrtok( NULL, s );
        i++;
    }

    return 0;
}

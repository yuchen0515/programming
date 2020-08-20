#include <stdio.h>
#include <stdint.h>

#include "examiner.h"
#include "player.h"

int main()
{    
    int32_t bull = 0, cow = 0;
    int32_t guess[4] = {0};
    
    setup();
    
    for( int32_t i = 0 ; i < 100 ; i++ )
    {
        int32_t result = 0;
        
        gen_guess( guess, bull, cow );
        result = check( guess, &bull, &cow );
        
        printf( "Guess: " );
            
        for( int32_t i = 0 ; i < 4 ; i++ )
        {
            printf( "%d ", guess[i] );
        }
        
        printf( "%d A %d B\n", bull, cow );
        
        if( result == 1 )
        {
            break;
        }
        else if( result == -1 )
        {
            printf( "Wrong input!!\n" );
        }
    }
    
    return 0;
}

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

struct _sBmpHeader
{
    char		bm[2];
    uint32_t	size;
    uint32_t	reserve;
    uint32_t	offset;
    uint32_t	header_size;
    uint32_t	width;
    uint32_t	height;
    uint16_t	planes;
    uint16_t	bpp;
    uint32_t	compression;
    uint32_t	bitmap_size;
    uint32_t	hres;
    uint32_t	vres;
    uint32_t	used;
    uint32_t	important;
}__attribute__ ((__packed__));

typedef struct _sBmpHeader sBmpHeader;

void print_bmp_header( sBmpHeader *pHeader )
{
    printf( "ID: %c%c\n", pHeader -> bm[0], pHeader -> bm[1] );
    printf( "Size: %u\n", pHeader -> size );
    printf( "Reserve: %u\n", pHeader -> reserve );
    printf( "Offset: %u\n", pHeader -> offset );
    printf( "Header Size: %u\n", pHeader -> header_size );
    printf( "Width: %u\n", pHeader -> width );
    printf( "Height: %u\n", pHeader -> height );
    printf( "Planes: %u\n", pHeader -> planes );
    printf( "Bits Per Pixel: %u\n", pHeader -> bpp );
    printf( "Compression: %u\n", pHeader -> compression );
    printf( "Bitmap Data Size: %u\n", pHeader -> bitmap_size );
    printf( "H-Resolution: %u\n", pHeader -> hres );
    printf( "V-Resolution: %u\n", pHeader -> vres );
    printf( "Used Colors: %u\n", pHeader -> used );
    printf( "Important Colors: %u\n", pHeader -> important );
    
    return;
}


int main()
{
    FILE	*pFile = NULL;
    FILE	*pFile2 = NULL;
    
    if( ( pFile = fopen( "maldives.bmp", "rb" ) ) == NULL )
    {
        printf( "File could not be opened!\n" );
        return 0;
    }
    
    if( ( pFile2 = fopen( "maldives_out.bmp", "wb" ) ) == NULL )
    {
        printf( "File could not be opened!\n" );
        return 0;
    }
    
    sBmpHeader	header;
    fread( &header, sizeof( header ), 1, pFile );
    fwrite( &header, sizeof( header ), 1, pFile2 );

    while( !feof( pFile ) )
    {
        uint8_t	original[1023] = {0};
        uint8_t modified[1023] = {0};
        
        size_t count = fread( original, 1, 1023, pFile );

		double v = 0;
        for( size_t i = 0 ; i < count ; i++ )
        {
			//大概這樣
			switch (i%3){
				case 0:
					//b
					v += original[i]*0.114;
					break;
				case 1:
					//g
					v +=  0.587* original[i];
					break;
				case 2: 
					//r
					v += 0.299 * original[i];
					
					modified[i-2] = v;
					modified[i-1] = v;
					modified[i] = v; 
					v = 0;
					break;
			}
        }
        
        fwrite( modified, count, 1, pFile2 );
        
    }
    
                
    fclose( pFile );
    fclose( pFile2 );
    
    return 0;
}

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "readfile.h"

struct _sBmpHeader{
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

/*
struct spixel{
	uint8_t b;
	uint8_t g;
	uint8_t r;
}__attribute__ ((__packed__));
typedef struct spixel pix;

struct spixel2{
	uint8_t t1;
	uint8_t t2;
}__attribute__ ((__packed__));
typedef struct spixel2 pix2;
*/


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


int main(){

    FILE	*pFile = NULL;
    FILE	*pFile2 = NULL;
	char *str = calloc(2, sizeof(char));
	
	printf("Please enter the input image name: ");
	readget(str, 2, stdin, 0);

    if( ( pFile = fopen(str, "rb" ) ) == NULL ){
        printf( "File could not be opened!\n" );
		perror("Error: ");
        return 0;
    }

    sBmpHeader	header;
    fread( &header, sizeof( header ), 1, pFile );

	if (pat_verify(header.bm, "BM*") !=1){
		printf("Your file isn't a BMP file!\n");
		return 0;
	}

	//char str2[9999];
	char *str2 = calloc(2, sizeof(char));

	printf("Please enter the output image name: ");
	readget(str2, 2, stdin, 0);
    
    if( ( pFile2 = fopen( str2, "wb" ) ) == NULL )
    {
        printf( "File could not be opened!\n" );
        return 0;
    }

	header.bpp = 16;
	header.offset = 54 + 12;
	header.bitmap_size = header.bitmap_size / 3 * 2;
	header.size = header.bitmap_size +54 +12;
	header.compression = 3;

	fwrite( &header, sizeof( header), 1, pFile2 );

	uint32_t mask[3] = {0x0000f800, 0x000007e0, 0x0000001f};
	fwrite( &mask, 12, 1, pFile2 );

	for (int32_t i = 0 ; i < (header.height * header.width) ; i++){
		uint8_t original[3] = {0};
		uint16_t modified = 0;

		size_t count = fread(original, 1, 3, pFile);
		
		//Blue
		original[0] = original[0] >> 3;
		//Green
		original[1] = original[1] >> 2;
		//Red
		original[2] = original[2] >> 3;

		modified = (original[2] << 11) | (original[1] << 5) | (original[0]);

		fwrite(&modified, 2, 1, pFile2);


	}

	fclose( pFile );
	fclose( pFile2 );

	printf("Done!\n");

	return 0;
}

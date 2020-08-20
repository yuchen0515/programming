#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "readfile.h"

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
	char *str = calloc(2, sizeof(char));
	
	printf("Please enter a bmp file: ");
	readget(str, 2, stdin, 0);

    
    if( ( pFile = fopen(str, "rb" ) ) == NULL )
    {
        printf( "File could not be opened!\n" );
		perror("Error: ");
        return 0;
    }

    sBmpHeader	header;
    fread( &header, sizeof( header ), 1, pFile );
	header.bpp = header.bpp/3 * 2;
	if (pat_verify(header.bm, "BM*") !=1){
		printf("Your file isn't a BMP file!\n");
		return 0;
	}

	int32_t count = 0;
	char str2[9999];
	while (*(str+count) != '\0'){
		*(str2+count) = *(str+count);
		count+=1;
	}
	count = 0;
	while (*(str2+count) != '\0'){
		if (*(str2+count) == '.'){
			*(str2+count) = '_';
			*(str2+count+1) = 'o';
			*(str2+count+2) = 'u';
			*(str2+count+3) = 't';
			*(str2+count+4) = '.';
			*(str2+count+5) = 'b';
			*(str2+count+6) = 'm';
			*(str2+count+7) = 'p';
			*(str2+count+8) = '\0';
			break;
		}
		count+=1;
	}
	
    
    if( ( pFile2 = fopen( str2, "wb" ) ) == NULL )
    {
        printf( "File could not be opened!\n" );
        return 0;
    }

	size_t enl = 1;
    

	int32_t width = header.width;
	int32_t height = header.height;


	fwrite( &header, sizeof( header ), 1, pFile2 );

	while( !feof( pFile ) )
	{
		pix original[width];
		uint16_t modified[width];

		fread(original, sizeof(pix), width, pFile);

		for (size_t i = 0 ; i < width; i++){
			uint16_t b = (original[i].b)>>3;
			uint16_t g = (original[i].g)>>3;
			uint16_t r = (original[i].r)>>3;
			modified[i] = (b<<0)|(g<<5)|(r<<10);

		}
		for (size_t j = 0 ; j < enl ; j++){
			fwrite(modified, sizeof(uint16_t), width, pFile2);
		}

	}

	fclose( pFile );
	fclose( pFile2 );

	return 0;
}

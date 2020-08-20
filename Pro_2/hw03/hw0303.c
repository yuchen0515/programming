#include "readfile.h"


//標頭檔struct
struct _sBmpHeader {
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
//取消cpu aligment, 不然大小會出事

typedef struct _sBmpHeader sBmpHeader;

//定義像素struct, b->g->r
struct spixel{
	uint8_t b;
	uint8_t g;
	uint8_t r;
}__attribute__ ((__packed__));
typedef struct spixel Spix;

//標頭檔的寫入
void write_header(sBmpHeader *pHeader, int32_t width, int32_t height){
	pHeader->bm[0] = 'B';
	pHeader->bm[1] = 'M';
	pHeader->size = width*height*3 + 54;
	pHeader->reserve = 0;
	pHeader->offset= 54;
	pHeader->header_size= 40;
	pHeader->width = width;
	pHeader->height= height;
	pHeader->planes= 1;
	pHeader->bpp = 24;
	pHeader->compression = 0;
	pHeader->bitmap_size = width*height*3;
	pHeader->hres = 9449;
	pHeader->vres = 9449;
	pHeader->used = 0;
	pHeader->important = 0;
}

//線性插值法
void interpret(Spix *cou, Spix *tp1, Spix *tp2, int32_t index, int32_t bound){
	cou->b = ((tp1->b)*(bound - index) + (tp2->b)*index)/bound;
	cou->g = ((tp1->g)*(bound - index) + (tp2->g)*index)/bound;
	cou->r = ((tp1->r)*(bound - index) + (tp2->r)*index)/bound;
}


//印出header的內容
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

	Spix tl, tr, bl, br;
	sBmpHeader header;

	FILE *pfile = NULL;
	int32_t height = 768, width = 1024;

	char *reg = calloc(2, sizeof(char));
	char *name = calloc(2, sizeof(char));

	//開檔，準備寫入
	printf("PLease enter the file: ");
	readget(name, 2, stdin, 1);

	if ((pfile = fopen(name, "w")) == NULL){
		printf("The file can't be opened!\n");
		perror("Error: ");
		return 0;
	}

	//使用者輸入4個角落的像素
	printf("Please enter (R,G,B) in the top left pixel: ");
	readget(reg, 2, stdin, 1);
	while ((pat_verify(reg, "?*,?*,?*")==0)){ 
		printf("Sorry! You should follow the format...\n");
		printf("Please enter (R,G,B) in the top left pixel: ");
		readget(reg, 2, stdin, 1);
	}
	sscanf(reg, "%hhu,%hhu,%hhu", &(tl.r), &(tl.g), &(tl.b));

	printf("Please enter (R,G,B) in the top right pixel: ");
	readget(reg, 2, stdin, 1);
	while ((pat_verify(reg, "?*,?*,?*")==0)){ 
		printf("Sorry! You should follow the format...\n");
		printf("Please enter (R,G,B) in the top right pixel: ");
		readget(reg, 2, stdin, 1);
	}
	sscanf(reg, "%hhu,%hhu,%hhu", &(tr.r), &(tr.g), &(tr.b));

	printf("Please enter (R,G,B) in the bottom left pixel: ");
	readget(reg, 2, stdin, 1);
	while ((pat_verify(reg, "?*,?*,?*")==0)){ 
		printf("Sorry! You should follow the format...\n");
		printf("Please enter (R,G,B) in the bottom left pixel: ");
		readget(reg, 2, stdin, 1);
	}
	sscanf(reg, "%hhu,%hhu,%hhu", &(bl.r), &(bl.g), &(bl.b));

	printf("Please enter (R,G,B) in the bottem right pixel: ");
	readget(reg, 2, stdin, 1);
	while ((pat_verify(reg, "?*,?*,?*")==0)){ 
		printf("Sorry! You should follow the format...\n");
		printf("Please enter (R,G,B) in the bottem right pixel: ");
		readget(reg, 2, stdin, 1);
	}
	sscanf(reg, "%hhu,%hhu,%hhu", &(br.r), &(br.g), &(br.b));

	write_header(&header, width, height);
	fwrite(&header, sizeof(header), 1, pfile);

	int32_t count = 0;

	//依線性插值法一一寫入
	for (int32_t j = 0 ; j < height; j++){
		Spix cou, cou2;
		interpret(&cou, &bl, &tl, count, height);
		interpret(&cou2, &br, &tr, count, height);

		for (int32_t i = 0 ; i < width ; i++){
			Spix wr;
			interpret(&wr, &cou, &cou2, i, width);
			fwrite(&wr, sizeof(Spix), 1, pfile);
		}
		count +=1;
	}


	fclose(pfile);
	printf("Done!\n");

	return 0;
}

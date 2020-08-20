#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
 
//定義option, write => w, extract => e
struct option long_options[] = {  
     { "write",  0, NULL, 'w' },  
     { "extract", 0, NULL, 'e' },  
     {  0, 0, 0, 0},  
};  

//定義像素
typedef struct _pixel{
	uint8_t r;
	uint8_t g;
	uint8_t b;
}S_pixel;

//bmp, jpg的rgb讀法不同
void transfer(S_pixel *temp){
	uint8_t tp = temp->r;
	temp -> r = temp -> b;
	temp -> b = tp;
}

//檔案備份, pfile => pfile2
void backup(FILE *pfile, FILE *pfile2){
	fseek(pfile, 0L, SEEK_SET);
	uint8_t temp = 0;
	while (!feof(pfile)){
		fread(&temp, 1, sizeof(uint8_t), pfile);
		fwrite(&temp, 1, sizeof(uint8_t), pfile2);
	}
	fseek(pfile, 0L, SEEK_SET);
}

//找識別碼 JPIF的位置
int64_t find_address(FILE *pfile, FILE *pfile2, int32_t choice){
	fseek(pfile, 0L, SEEK_SET);
	uint8_t temp = 0;
	while (!(feof(pfile))){
		int64_t address = ftell(pfile);
		fread(&temp, 1, sizeof(uint8_t), pfile);
		if (choice == 1) fwrite(&temp, 1, sizeof(uint8_t), pfile2);
		if (temp == 0x4a){
			uint8_t *tp = calloc(4, sizeof(uint8_t));
			for (int32_t i = 0 ; i < 4 ; i++){
				fread(&tp[i], 1, sizeof(uint8_t), pfile);
			}
			if (tp[0] == 0x46 && tp[1] ==0x49 && tp[2] ==0x46 && tp[3] == 0x00){
				if (choice){
					for (int32_t i = 0 ; i < 4; i++){
						fwrite(&tp[i], 1, sizeof(uint8_t), pfile2);
					}
				}
				return ftell(pfile);
			}else{
				fseek(pfile, 1L, address);
				continue;
			}
		}
	}
	return -1;
}

//定義標頭檔結構
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


//標頭檔的寫入
void write_header(sBmpHeader *pHeader, int32_t width, int32_t height){
	pHeader->bm[0] = 'B';
	pHeader->bm[1] = 'M';
	pHeader->size = width * height * 3 + 54;
	pHeader->reserve = 0;
	pHeader->offset= 54;
	pHeader->header_size= 40;
	pHeader->width = width;
	pHeader->height= -1 * height;
	pHeader->planes= 1;
	pHeader->bpp = 24;
	pHeader->compression = 0;
	pHeader->bitmap_size = width * height * 3;
	pHeader->hres = 9449;
	pHeader->vres = 9449;
	pHeader->used = 0;
	pHeader->important = 0;
}


int main(int argc, char *argv[]){
	sBmpHeader header;

    int32_t c = 0, index = 0;
	int32_t record_w = 0, record_e = 0;

	//處理參數
    while ((c = getopt_long(argc, argv, "we", long_options, &index)) != -1 ){
        switch( c ){
            case 'w':
				record_w = 1;
                break;
			case 'e':
				record_e = 1;
				break;
            default:
				printf("Your argument input error!\n");
				return 0;
        }
    }

	//判斷不合理的輸入
	if (record_e==0 && record_w ==0){
		printf("You not input argument!\n");
		return 0;
	}else if (record_e == 1 && record_w ==1){
		printf("You should choose an option...no both.\n");
		return 0;
	}else if (argc !=4){
		printf("You should input an option, jpg, bmp filename\n");
		return 0;
	}

    FILE *pfile = NULL, *pfile2 = NULL, *pfile3 = NULL;
	uint8_t temp = 0, xthumbnail = 0, ythumbnail = 0;

	if ((pfile = fopen(argv[2], "r"))==NULL){
		printf( "File could not be opened!\n" );
		return 0;
	}
	if ((pfile3 = fopen("backup.jpg", "w"))==NULL){
		printf( "File could not be opened!\n" );
		return 0;
	}

	backup(pfile, pfile3);
	fclose(pfile3);

	//extract
	if (record_e == 1){
		fprintf(stderr, "Extract the jpg file's thumbnail to the bmp");
		//製造類似進度條的效果	
		for (int32_t i = 0 ; i < 6 ; i++){
			usleep(250000);
			fprintf(stderr, ".");
		}
		puts("");

		if ((pfile2 = fopen(argv[3], "w"))==NULL){
			printf( "File could not be opened!\n" );
			return 0;
		}

		//找JPIF在哪，同時判斷是否存在，不存在當然不是JPG檔
		if (find_address(pfile, pfile3, 0) == -1) printf("Your input file isn't a jpg.\n");

		//識別碼後面7 bytes 會放縮圖資訊
		for (int32_t i = 0; i < 7 ;i++) fread(&temp, 1, sizeof(uint8_t), pfile);

		fread(&xthumbnail, 1, sizeof(uint8_t), pfile);
		fread(&ythumbnail, 1, sizeof(uint8_t), pfile);
		uint32_t  nthumbnail = xthumbnail * ythumbnail;

		//讀取縮圖大小的資訊，存到bmp內
		S_pixel cur;
		write_header(&header, xthumbnail, ythumbnail);
		fwrite(&header, sizeof(header), 1, pfile2);
		for (int32_t i = 0 ; i < nthumbnail ; i++){
			fread(&cur, 1, sizeof(S_pixel), pfile);
			transfer(&cur);
			fwrite(&cur, 1, sizeof(S_pixel), pfile2);
		}


	//write
	}else if (record_w ==1){
		fprintf(stderr, "(Over)Write the bmp file to the jpg file's thumbnail");
		//製造進度條的效果
		for (int32_t i = 0 ; i < 6 ; i++){
			usleep(250000);
			fprintf(stderr, ".");
		}
		puts("");

		fclose(pfile);

		if ((pfile2 = fopen(argv[3], "r"))==NULL){
			printf( "File could not be opened!\n" );
			return 0;
		}

		//讀掉bmp的header
		fread(&header, 1, sizeof(header), pfile2);

		//height有可能是負數，因此我們要限定他為正數才不會出問題
		header.height = abs(header.height);

		//使用者輸入大於 縮圖可放的大小，就告知使用者輸入錯誤
		if (header.width > 255 || header.height >255){
			printf("%d %d\n", header.width, header.height);
			printf("Your bmp is too large(width and height > 255)!\n");
			return 0;
		}

		if ((pfile = fopen(argv[2], "w"))==NULL){
			printf( "File could not be opened!\n" );
			return 0;
		}
		if ((pfile3 = fopen("backup.jpg", "r"))==NULL){
			printf( "File could not be opened!\n" );
			return 0;
		}

		//開始找識別碼(JPIF)，找不到輸出錯誤
		if (find_address(pfile3, pfile, 1) == -1) printf("Your input file isn't a jpg.\n");

		//讀到縮圖位置
		for (int32_t i = 0; i < 7 ;i++){
			fread(&temp, 1, sizeof(uint8_t), pfile3);
			fwrite(&temp, 1, sizeof(uint8_t), pfile);
		}
		fread(&xthumbnail, 1, sizeof(uint8_t), pfile3);
		fwrite(&header.width, 1, sizeof(uint8_t), pfile);
		fread(&ythumbnail, 1, sizeof(uint8_t), pfile3);
		fwrite(&header.height, 1, sizeof(uint8_t), pfile);

		//在pfile3把縮圖的資訊讀掉
		uint32_t  nthumbnail = xthumbnail * ythumbnail;
		S_pixel cur[nthumbnail], current;
		fread(&cur, sizeof(S_pixel), nthumbnail, pfile3);

		//開始把bmp檔案寫入pfile
		while (!feof(pfile2)){
			fread(&current, 1, sizeof(S_pixel), pfile2);
			transfer(&current);
			fwrite(&current, 1, sizeof(S_pixel), pfile);
		}

		//把pfile3後面的jpg相關資訊寫回pfile
		while (!feof(pfile3)){
			fread(&temp, 1, sizeof(uint8_t), pfile3);
			fwrite(&temp, 1, sizeof(uint8_t), pfile);
		}

		fclose( pfile3 );
	}


	fclose( pfile );
	fclose( pfile2 );
	printf("Done!\n");

	return 0;
}

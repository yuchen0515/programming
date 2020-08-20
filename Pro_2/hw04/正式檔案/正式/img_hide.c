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
     { "bits", 0, NULL, 'b' },  
     {  0, 0, 0, 0},  
};  

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


//得到檔案大小
uint32_t get_file_size(FILE *pfile){
	int32_t regard = ftell(pfile);
	fseek(pfile, 0L, SEEK_SET);

	int32_t sta = ftell(pfile);
	fseek(pfile, 0L, SEEK_END);

	int32_t dis = ftell(pfile) - sta;
	fseek(pfile, regard, SEEK_SET);

	return dis;
}


int main(int32_t argc, char *argv[]){
	sBmpHeader header;

    int32_t c = 0, index = 0;
	int32_t record_w = 0, record_e = 0, record_b = 0;
	int32_t bits = 1, b_count = 1, opt_get = -1;

	if (argc < 4 || argc > 7){
		printf("Your argument input error!\n");
		return 0;
	}

	//處理參數
	while ((c = getopt_long(argc, argv, "web:", long_options, &index)) != -1 ){
		switch( c ){
			case 'w':
				record_w = 1;
				break;
			case 'e':
				record_e = 1;
				break;
			case 'b':
				record_b = 1;
				opt_get = b_count;
				break;
			default:
				printf("Your argument input error!\n");
				return 0;
		}
		b_count +=1;
	}

	//接收bits的數值，若沒有輸入則預設為1
	if (opt_get != -1)
		sscanf(argv[opt_get+1], "%d", &bits);

	if (!(bits >= 1 && bits <= 8)){
		printf("Your bits argument should be 1 <= x <= 8.\n");
		return 0;
	}

	if (!(record_w ^ record_e)){
		printf("Your option error!\n");
		return 0;
	}

	FILE *cfile = NULL, *sfile = NULL, *bfile = NULL;

	if ((cfile = (fopen(argv[argc-2], "r")))==NULL){
		printf("The file don't be opened!\n");
		perror("Error: ");
		return 0;
	}
	if ((bfile = (fopen("cover_bmp_backup", "w")))==NULL){
		printf("The file don't be opened!\n");
		perror("Error: ");
		return 0;
	}

	backup(cfile, bfile);

	uint32_t tp = 0;
	uint32_t mask = 0, mask2 = 0, save = 0;
	uint32_t cou = 0, ind = bits, check = 0;

	fclose(bfile);
	bfile = fopen("cover_bmp_backup", "r");
	fread(&header, 1, sizeof(sBmpHeader), bfile);

	//extract
	if (record_e == 1){
		sfile = fopen(argv[argc-1], "w");
		int32_t rev = header.reserve;
		int32_t cou_w = 1;
		while (1){
			if (cou == 8){
				fwrite(&tp, 1, sizeof(uint8_t), sfile);
				if (cou_w >= rev) break;
				tp = 0;
				cou = 0;
				cou_w +=1;
			}

			if (bits == ind){
				fread(&save, 1, sizeof(uint8_t), bfile);
				ind = 0;
			}
			tp = (tp << 1) + ((save >> ind) & 1);
			cou+=1;
			ind+=1;
		}
	//write
	}else if (record_w == 1){
		if ((sfile = (fopen(argv[argc-1], "r")))==NULL){
			printf("The file don't be opened!\n");
			perror("Error: ");
			return 0;
		}
		uint32_t sfile_size = get_file_size(sfile);
		uint32_t cfile_size = get_file_size(cfile);

		if (sfile_size*8 > (cfile_size - 54)*bits){
			printf("Your cover_bmp is too short to save secret file.\n");
			return 0;
		}
		header.reserve = sfile_size;

		fclose(cfile);
		cfile = fopen(argv[argc-2], "w");
		fwrite(&header, 1, sizeof(sBmpHeader), cfile);

		while (1){
			if (cou == 0){
				fread(&tp, 1, sizeof(uint8_t), sfile);
				cou = 8;
				mask = 1 << 7;
			}
			if (ind == bits){
				if (check)
					fwrite(&save, 1, sizeof(uint8_t), cfile);
				if (feof(sfile)) break;
				ind = 0;
				fread(&save, 1, sizeof(uint8_t), bfile);
				check = 1;
				save = (save >> bits) << bits;
			}
			cou -=1;
			mask2 = ((tp & mask)>>cou) << ind;
			mask >>= 1;
			save |= mask2;
			ind+=1;
		}
		while (!feof(bfile)){
			fread(&save, 1, sizeof(uint8_t), bfile);
			fwrite(&save, 1, sizeof(uint8_t), cfile);
		}
	}


	fclose(sfile);
	fclose(bfile);
	fclose(cfile);

	printf("Done!\n");

	return 0;
}

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void eight_ability();
void choose_print();
void choose_side();
void di_role();
void same_role();
void again_modify();
void modify(char *str);
void backup(FILE *pfile, FILE *pfile2, char *chr, char *str);
void find_address(FILE *pfile3, int32_t side, int32_t role, int32_t *modi1, int32_t *modi2);
int32_t transfr(int32_t temp);
void modi_data(FILE *pfile, FILE *pfile2, char *filename, int32_t modi1, int32_t modi2, int32_t num, int32_t cho);

int main(){

	FILE *pfile = NULL; FILE *pfile2 = NULL;
	FILE *pfile3 = NULL;

	char *filename = calloc(501, sizeof(char));

	printf("Please enter your data file: ");
	fgets(filename, 500, stdin);
	modify(filename);

	if ((pfile = fopen(filename, "r"))==NULL){
		printf("The file don't be opened!\n");
		perror("Error: ");
		return 0;
	}
	fclose(pfile);

	if ((pfile2 = fopen("hw0304_data.txt", "r"))==NULL){
		printf("The file don't be opened!\n");
		perror("Error: ");
		return 0;
	}

	if ((pfile3 = fopen("hw0304_temp", "w"))==NULL){
		printf("The file don't be opened!\n");
		perror("Error: ");
		return 0;
	}
	fclose(pfile3);
	backup(pfile, pfile3, "hw0304_temp", filename);

	while (1){
		int32_t choose_1 = 0;
		int32_t choose_2 = 0;
		int32_t choose_3 = 0;
		int32_t ability = 0;
		int32_t num_mod = 0;
		int32_t modi1 = 0, modi2 = 0;
		choose_print();
		scanf("%d", &choose_1);
		if (choose_1 == 1){
			while (1){
				choose_side();
				scanf("%d", &choose_2);
				if (choose_2 == 1){
					while (1){
						di_role();
						scanf("%d", &choose_3);
						if (choose_3 >= 1 && choose_3 <= 108){
							while (1){
								eight_ability();
								scanf("%d", &ability);
								if (ability >= 1 && ability <= 12){
									printf("請輸入你要修改的數值: ");
									scanf("%d", &num_mod);
									find_address(pfile2, 0, choose_3, &modi1, &modi2);
									modi_data(pfile, pfile3, filename, modi1, modi2, num_mod, ability);
									backup(pfile, pfile3, "hw0304_temp", filename);
								}else if (ability == 13){
									break;
								}else printf("Input Error! Please enter again!\n");
							}
						}else if (choose_3 == 109) break;
						else printf("Input Error! Please enter again!\n");
					}
				}else if (choose_2 == 2){
						same_role();
						scanf("%d", &choose_3);
						if (choose_3 >= 1 && choose_3 <= 75){
							while (1){
								eight_ability();
								scanf("%d", &ability);
								if (ability >= 1 && ability <= 12){
									printf("請輸入你要修改的數值: ");
									scanf("%d", &num_mod);
									find_address(pfile2, 1, choose_3, &modi1, &modi2);
									modi_data(pfile, pfile3, filename, modi1, modi2, num_mod, ability);
									backup(pfile, pfile3, "hw0304_temp", filename);
									printf("Done!\n\n");
								}else if (ability == 13){
									break;
								}else printf("Input Error! Please enter again!\n");
							}
						}else if (choose_3 == 76) break;
						else printf("Input Error! Please enter again!\n");
				}else if (choose_2 == 3){
					break;
				}else printf("Input Error! Please enter again!\n");
			}
		}else if (choose_1 == 2){
			
			while (1){
				printf("-------------選擇-----------\n");
				printf("1) 軍務省預算\n");
				printf("2) 統帥本部預算\n");
				printf("3) 回上一頁\n");
				printf("----------------------------\n");
				printf("choose: ");
				scanf("%d", &choose_2);
				uint64_t money = 0;
				if (choose_2 == 1){
					printf("請輸入數值: ");
					scanf("%lu", &money);
					modi_data(pfile, pfile3, filename, 142, 67756, money, 14);
					backup(pfile, pfile3, "hw0304_temp", filename);
					printf("Done!\n\n");
				}else if (choose_2 == 2){
					printf("請輸入數值: ");
					scanf("%lu", &money);
					modi_data(pfile, pfile3, filename, 146, 67760, money, 14);
					backup(pfile, pfile3, "hw0304_temp", filename);
					printf("Done!\n\n");

				}else if (choose_2 == 3){
					break;
				}
			}

		}else if (choose_1 == 3){ 
			uint64_t money = 0;
			printf("請輸入數值: ");
			scanf("%lu", &money);
			modi_data(pfile, pfile3, filename, 204, 67818, money, 14);
			backup(pfile, pfile3, "hw0304_temp", filename);
			printf("Done!\n\n");
		}else if (choose_1 == 4){
			break;
		}else printf("Input Error! Please enter again!\n");
	}
	

	fclose(pfile2);
	return 0;
}

void find_address(FILE *pfile3, int32_t side, int32_t role, int32_t *modi1, int32_t *modi2){
	int32_t count = 108*side + role;
	int32_t temp1 = 0, temp2 = 0;
	char *str = calloc(1001, sizeof(char));
	int32_t i = 0;
	while (1){
		i+=1;
		fscanf(pfile3, "%d %d", &temp1, &temp2);
		fgets(str, 1000, pfile3);
		if (i == count){
			*modi1 = temp1;
			*modi2 = temp2;
			fseek(pfile3, 0L, SEEK_SET);
			return;

		}
		if (feof(pfile3)){
			fseek(pfile3, 0L, SEEK_SET);
			return;
		}
	}
	


}

void backup(FILE *pfile, FILE *pfile2, char *chr, char *str){
	pfile2 = fopen(chr, "wb");
	pfile = fopen(str, "rb");
	uint32_t temp = 0;
	while (!(feof(pfile))){
		fread(&temp, 1, sizeof(uint8_t), pfile);
		fwrite(&temp, 1, sizeof(uint8_t), pfile2);
	}
	fclose(pfile);
	fclose(pfile2);
	return;
}

void modi_data(FILE *pfile, FILE *pfile2, char *filename, int32_t modi1, int32_t modi2, int32_t num, int32_t cho){
	int32_t address = transfr(cho)+modi1;
	int32_t address2 = transfr(cho)+modi2;
	pfile = fopen(filename, "w");
	pfile2 = fopen("hw0304_temp", "r");
	uint32_t temp = 0;
	uint64_t count = 0;
	while (!(feof(pfile2))){
		if (count == address){
			if (cho != 1 && !(cho >= 10 && cho <=12)){
				fread(&temp, 1, sizeof(uint8_t), pfile2);
				fwrite(&num, 1, sizeof(uint8_t), pfile);
				count+=1;
			}else if (cho == 1 || cho == 14){
				fread(&temp, 1, sizeof(uint32_t), pfile2);
				fwrite(&num, 1, sizeof(uint32_t), pfile);
				count+=4;
			}else{
				fread(&temp, 1, sizeof(uint16_t), pfile2);
				fwrite(&num, 1, sizeof(uint16_t), pfile);
				count+=2;
			}
		}else if (count == address2){
			if (cho != 1 && !(cho >= 10 && cho <=12)){
				fread(&temp, 1, sizeof(uint8_t), pfile2);
				fwrite(&num, 1, sizeof(uint8_t), pfile);
				count+=1;
			}else if (cho == 1 || cho==14){
				fread(&temp, 1, sizeof(uint32_t), pfile2);
				fwrite(&num, 1, sizeof(uint32_t), pfile);
				count+=4;
			}else{
				fread(&temp, 1, sizeof(uint16_t), pfile2);
				fwrite(&num, 1, sizeof(uint16_t), pfile);
				count+=2;
			}
		}else{ 
			fread(&temp, 1, sizeof(uint8_t), pfile2);
			fwrite(&temp, 1, sizeof(uint8_t), pfile);
			count +=1;
		}
	}
	fclose(pfile);
	fclose(pfile2);

}
void modify(char *str){
	int32_t count = 0;
	while (1){
		if (*(str+count) == '\n' || *(str+count) == '\0'){
			*(str+count) = '\0';
			return; }
		count+=1;
	}
}

void choose_print(){
	printf("\n\n-------主選單------\n");
	printf("1) 修改屬性值\n");
	printf("2) 修改帝國軍預算\n");
	printf("3) 修改同盟軍預算\n");
	printf("4) 離開\n");
	printf("-------------------\n");
	printf("choose: ");
}

void choose_side(){
	printf("\n\n---選擇角色陣營---\n");
	printf("1) 帝國軍\n");
	printf("2) 同盟軍\n");
	printf("3) 回上一頁\n");
	printf("-------------------\n");
	printf("choose: ");
}

void again_modify(){
	printf("\n\n-------詢問--------\n");
	printf("您還要再修改其能力值嗎?\n");
	printf("1) 好\n");
	printf("2) 不要，回上一頁!\n");
	printf("-------------------\n");
	printf("choose: ");
}

void eight_ability(){
	printf("\n\n-------能力值--------\n");
	printf("您要修改哪一個能力值呢?\n");
	printf("1) 功績(0-32767)\t");
	printf("2) 統率(0-255)\n");
	printf("3) 營運(0-255)\t\t");
	printf("4) 情報(0-255)\n");
	printf("5) 機動(0-255)\t\t");
	printf("6) 攻擊(0-255)\n");
	printf("7) 防禦(0-255)\t\t");
	printf("8) 陸戰(0-255)\n");
	printf("9) 空戰(0-255)\t\t");
	printf("10) 政治工作(0-32767)\n");
	printf("11) 情報工作(0-32767)\t");
	printf("12) 軍事工作(0-32767)\n");
	printf("13) 回上一頁\n");
	printf("-------------------\n");
	printf("choose: ");
}


int32_t transfr(int32_t temp){
	if (temp == 14) return 0;
	int32_t tp[] = {0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 14};
	return tp[temp-1]+2;
}

void di_role(){
	printf("\n\n-------帝國軍------\n");
	printf("1)羅嚴克拉姆\t\t\t");
	printf("2)山德斯\t\t\t");
	printf("3)巴爾豪薩\t\t\t");
	printf("4)卡姆胡巴\t\t\t");
	printf("5)卡爾納普\n");
	printf("6)古利茲\t\t\t");
	printf("7)古雷沙\t\t\t");
	printf("8)古魯堅休提倫\t\t\t");
	printf("9)布克斯提夫德\t\t\t");
	printf("10)布拉斯契\n");
	printf("11)布朗胥百克\t\t\t");
	printf("12)布連塔諾\t\t\t");
	printf("13)布爾達哈\t\t\t");
	printf("14)瓦列\t\t\t\t");
	printf("15)皮羅\n");
	printf("16)立典亥姆\t\t\t");
	printf("17)立典拉德\t\t\t");
	printf("18)特勞斯\t\t\t");
	printf("19)休勒\t\t\t\t");
	printf("20)列佛爾特\n");
	printf("21)列肯道夫\t\t\t");
	printf("22)吉爾菲艾斯\t\t\t");
	printf("23)安森巴哈\t\t\t");
	printf("24)米達麥亞\t\t\t");
	printf("25)艾亨道夫\n");
	printf("26)艾倫博克\t\t\t");
	printf("27)艾爾拉赫\t\t\t");
	printf("28)艾齊納哈\t\t\t");
	printf("29)佛格\t\t\t\t");
	printf("30)何夫麥斯塔\n");
	printf("31)克那普斯坦\t\t\t");
	printf("32)克里希\t\t\t");
	printf("33)克拉傑\t\t\t");
	printf("34)克拉普夫\t\t\t");
	printf("35)克斯拉\n");
	printf("36)克萊巴\t\t\t");
	printf("37)克羅第瓦魯\t\t\t");
	printf("38)坎普\t\t\t\t");
	printf("39)宋巴爾特\t\t\t");
	printf("40)宋年菲爾斯\n");
	printf("41)希德斯哈姆\t\t\t");
	printf("42)狄克爾\t\t\t");
	printf("43)狄塔斯多夫\t\t\t");
	printf("44)貝爾肯格林\t\t\t");
	printf("45)亞特林肯\n");
	printf("46)奇斯里\t\t\t");
	printf("47)奈西巴哈\t\t\t");
	printf("48)拉傑爾\t\t\t");
	printf("49)林查\t\t\t\t");
	printf("50)法倫海特\n");
	printf("51)阿姆斯道爾\t\t\t");
	printf("52)哈爾巴休泰\t\t\t");
	printf("53)拜耶爾藍\t\t\t");
	printf("54)派特利肯\t\t\t");
	printf("55)胥夫特\n");
	printf("56)迪爾克先\t\t\t");
	printf("57)修姆德\t\t\t");
	printf("58)修特克豪簡\t\t\t");
	printf("59)修特萊\t\t\t");
	printf("60)修萊雅\n");
	printf("61)夏伍汀\t\t\t");
	printf("62)庫典森\t\t\t");
	printf("63)格利魯帕爾\t\t\t"); 
	printf("64)格留尼曼\t\t\t");
	printf("65)格雷布納\n");
	printf("66)特奈傑\t\t\t");
	printf("67)曹肯\t\t\t\t");
	printf("68)梅克林格\t\t\t");
	printf("69)梅爾卡茲\t\t\t");
	printf("70)畢典菲爾特\n");
	printf("71)荷爾茲拜亞\t\t\t");
	printf("72)連內肯普\t\t\t");
	printf("73)麥佛赫\t\t\t");
	printf("74)傑克特\t\t\t");
	printf("75)斯坦赫夫\n");
	printf("76)斯特汀\t\t\t");
	printf("77)舒坦梅茲\t\t\t");
	printf("78)舒奈德\t\t\t");
	printf("79)舒馬赫\t\t\t");
	printf("80)華根賽爾\n");
	printf("81)萊博爾\t\t\t");
	printf("82)菲列格爾\t\t\t");
	printf("83)菲爾納\t\t\t");
	printf("84)費賽尼亞\t\t\t");
	printf("85)奧夫雷沙\n");
	printf("86)奧貝斯坦\t\t\t");
	printf("87)雷姆拉\t\t\t");
	printf("88)流肯\t\t\t\t");
	printf("89)維拉\t\t\t\t");
	printf("90)豪夫\n");
	printf("91)豪普特曼\t\t\t");
	printf("92)德洛伊傑\t\t\t");
	printf("93)德瑞文滋\t\t\t");
	printf("94)摩特\t\t\t\t");
	printf("95)歐拉\n");
	printf("96)歐根\t\t\t\t");
	printf("97)魯比茲\t\t\t");
	printf("98)魯茲\t\t\t\t");
	printf("99)諾多海姆\t\t\t");
	printf("100)錦茲\n");
	printf("101)繆拉\t\t\t");
	printf("102)賽貝爾\t\t\t");
	printf("103)薩姆\t\t\t");
	printf("104)謬肯貝爾加\t\t\t");
	printf("105)謬傑爾\n");
	printf("106)謬森休特\t\t\t");
	printf("107)羅嚴塔爾\t\t\t");
	printf("108)蘭斯貝爾克\n");
	printf("109) 回上一頁\n");
	printf("-------------------\n");
	printf("choose: ");
}

void same_role(){
	printf("\n\n-------同盟軍------\n");
	printf("1)巴格達胥\t\t\t");
	printf("2)比克古\t\t\t");
	printf("3)卡介倫\t\t\t");
	printf("4)卡爾先\t\t\t");
	printf("5)可那利\n");
	printf("6)史托克斯\t\t\t");
	printf("7)史路茲卡利達\t\t\t");
	printf("8)尼爾遜\t\t\t");
	printf("9)布拉多喬\t\t\t");
	printf("10)布隆茲\n");
	printf("11)布魯姆哈爾特\t\t\t");
	printf("12)伍爾夫\t\t\t");
	printf("13)先寇布\t\t\t");
	printf("14)托達\t\t\t");
	printf("15)自由行星同盟最高評議會\n");
	printf("16)艾凡思\t\t\t");
	printf("17)艾默森\t\t\t");
	printf("18)克魯思齊\t\t\t");
	printf("19)沙尼亞\t\t\t");
	printf("20)貝伊\n");
	printf("21)貝歐拉\t\t\t");
	printf("22)邦斯格爾\t\t\t");
	printf("23)阮文紹\t\t\t");
	printf("24)亞典波羅\t\t\t");
	printf("25)亞修\n");
	printf("26)亞達\t\t\t\t");
	printf("27)亞爾。沙列姆\t\t\t");
	printf("28)姆萊\t\t\t\t"); 
	printf("29)帕斯里契夫\t\t\t");
	printf("30)拉普\n");
	printf("31)拉歐\t\t\t\t");
	printf("32)林滋\t\t\t\t");
	printf("33)波布蘭\t\t\t");
	printf("34)波羅汀\t\t\t");
	printf("35)法菲爾\n");
	printf("36)邱\t\t\t\t");
	printf("37)阿普頓\t\t\t");
	printf("38)威迪\t\t\t\t");
	printf("39)洛克維爾\t\t\t");
	printf("40)科庫蘭\n");
	printf("41)科爾德威\t\t\t");
	printf("42)夏爾強\t\t\t");
	printf("43)庫布斯里\t\t\t");
	printf("44)席特尼\t\t\t");
	printf("45)D。格林希爾\n");
	printf("46)F。格林希爾\t\t\t");
	printf("47)馬利諾\t\t\t");
    printf("48)馬里涅汀\t\t\t");
    printf("49)馬斯喀尼\t\t\t");
    printf("50)高尼夫\n");
    printf("51)I。高尼夫\t\t\t");
    printf("52)塔特雷\t\t\t");
    printf("53)畢羅萊尼\t\t\t");
    printf("54)莫頓\t\t\t\t");
    printf("55)陳\n");
    printf("56)華利蒙特\t\t\t");
    printf("57)菲爾茲\t\t\t");
    printf("58)費雪\t\t\t\t");
    printf("59)雅拉肯\t\t\t");
    printf("60)楊\n");
    printf("61)賈瓦夫\t\t\t");
    printf("62)路菲普\t\t\t");
    printf("63)赫伍得\t\t\t");
    printf("64)德森\t\t\t\t");
    printf("65)慕亞\n");
    printf("66)魯格拉希\t\t\t");
    printf("67)霍克\t\t\t\t");
    printf("68)戴休\t\t\t\t");
    printf("69)羅波斯\t\t\t");
    printf("70)波特\n");
    printf("71)瑪林道夫\t\t\t");
	printf("72)梅爾卡茲\t\t\t");
	printf("73)舒奈德\t");
	printf("74)敏茲\t\t");
	printf("75)馬遜\n");
	printf("76)回上一頁\n");
	printf("-------------------\n");
	printf("choose: ");
}

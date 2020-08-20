#include "readfile.h"

//ac_code剛開始的標頭檔, int main
void ptcfile(FILE *cfile, char hfile[], int32_t t){
	fprintf(cfile, "#include \"%s\"\n", hfile);
	fprintf(cfile, "#include <stdio.h>\n");
	fprintf(cfile, "#include <stdint.h>\n\n");
	
	fprintf(cfile, "int main(){\n\n");
	fprintf(cfile, "\tprintf(\"Running %d test cases:\\n\");\n\n", t);
}

//驗證函數是否正確的判斷式
void acpt(FILE *cfile, int32_t exp, char pat[], int32_t *count){
	fprintf(cfile, "\tprintf(\"%d) %s: \");\n", *count, pat);
	fprintf(cfile, "\tif ( %s == %d ) ", pat, exp);
	fprintf(cfile, "printf(\"PASS\\n\");\n");
	fprintf(cfile, "\telse ");
	fprintf(cfile, "printf(\"Return: %%d, Wanted: %d\\n\", %s);\n\n", exp, pat);
	*count +=1;
}

//收尾的 return 0;
void endd(FILE *cfile){
	fprintf(cfile, "\treturn 0;\n");
	fprintf(cfile, "}\n");
}

int main(){

	FILE *text = NULL, *makefile = NULL, *cfile = NULL;
	char *mol_inc = "INCLUDE(*)", *mol_req = "REQUIRE(*)";
	char *mol_exp = "EXPECT_EQ(?*,?*(?*));";
	char str[999999], *filename = calloc(2, sizeof(char));
	int32_t tt = 0;

	printf("Please enter the test script: ");
	readget(filename, 2, stdin, 1);

	if ((text = fopen(filename, "r")) ==NULL){
		printf("The script text don't be opened!\n");
		perror("Error: ");
		return 0;
	}
	while (!(feof(text))){
		if (readget(str, 999999, text, 1) == NULL) break;
		if (pat_verify(str, mol_exp)) tt+=1; 
	}
	fclose(text);
	text = fopen(filename, "r");

	if ((makefile = fopen("Makefile", "w")) == NULL){
		printf("The Makefile don't be opened!\n");
		perror("Error: ");
		return 0;
	}
	if ((cfile = fopen("ac_code.c", "w")) == NULL){
		printf("ac_code.c and Makefile don't be generated.\n");
		perror("Error: ");
		return 0;
	}

	char req[999], inc[999];
	int32_t che_req = 0, che_inc = 0, wri = 0;

	while (!(feof(text))){
		if (readget(str, 999999, text, 1) == NULL) break;

		//INCLUDE and REQUIRE
		if (che_req == 0 || che_inc ==0){
			if (che_req == 0 && pat_verify(str, mol_req)){
				che_req = 1;
				sscanf(str, "REQUIRE(%s)", req);
				req[strlen(req)-1] = '\0';
			}else if (che_inc ==0 && pat_verify(str, mol_inc)){
				che_inc = 1;
				sscanf(str, "INCLUDE(%s)", inc);
				inc[strlen(inc)-1] = '\0';
			}else printf("Your INCLUDE or REQUIRE format error!\n");

		//EXPECT_EQ
		}else if (pat_verify(str, mol_exp)){
			if (wri ==0){
				ptcfile(cfile, inc, tt);
				wri = 1;
				tt = 1;
			}
			int32_t ans = 0;
			char pt[999];
			sscanf(str, "EXPECT_EQ(%d,%s);", &ans, pt);
			pt[strlen(pt)-2] = '\0';
			acpt(cfile, ans, pt, &tt);

		//FORMAT ERROR
		}else if (strlen(str)!=0){
			printf("Your format error!\n");
			return 0;
		}
	}
	endd(cfile);

	//makefile append
	fprintf(makefile, "all:\n");
	fprintf(makefile, "\tgcc ac_code.c %s -c\n", req);
	inc[strlen(inc)-1] = 'o';
	fprintf(makefile, "\tgcc ac_code.o %s -o ac_code\n", inc);
	printf("ac_code.c and Makefile are generated.\n");

	fclose(text);
	fclose(makefile);
	fclose(cfile);

	return 0;
}

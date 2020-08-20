#include "readfile.h"

//檢查後面有沒有等號
int32_t che_eq(char *str){
	int32_t count = 0 ;
	while (*(str+count) != '\n' && *(str+count) !='\0'){
		if (*(str+count) == '=') return 1;
		count+=1;
	}
	return 0;
}

//直接印到換行或結束
int32_t ptend(char *str, int32_t count, FILE *file){
	while (1){
		if (*(str+count) != '\0') fprintf(file, "%c", *(str+count));
		if (*(str+count) == '\0' || *(str+count) == '\n'){
			count +=1;
			break;
		}
		count +=1;
	}
	return count;
}


int main(){

	FILE *file = NULL, *output = NULL;
	int32_t count = 0, ind = 0 , che = 0;

	char com[99999];
	char *file_name = calloc(2, sizeof(char)), str[999999];
	char *option = calloc(2, sizeof(char)), *value = calloc(2, sizeof(char));

	printf("Please enter a file name: ");
	readget(file_name, 2, stdin, 1);

	if ((file = fopen(file_name, "r")) ==NULL){
		printf("Your file don't be opened!\n");
		perror("Error: ");
		return 0;
	}

	printf("Option: ");
	readget(option, 2, stdin, 1);
	printf("Value: ");
	readget(value, 2, stdin, 1);

	while (!(feof(file))){
		fscanf(file, "%c", (str+count));
		count+=1;
	}
	*(str+count) = '\0';
	fclose(file);

	output = fopen(file_name, "w");

	count = 0;
	while (*(str+count) != '\0'){
		if (*(str+count) =='#'){
			ind = 0;
			count = ptend(str, count, output);
		}else if(*(str+count) == ' '){
			if (che_eq(str+count)==0){
				*(com+ind) = '\0';
				fprintf(output, "%s", com);
				ind = 0;
				fprintf(output, " ");
			}
			count+=1;
		}else if (*(str+count) == '='){
			*(com+ind) = '\0';
			fprintf(output, "%s=", com);
			count+=1;
			ind = 0;
			if (strcmp(com, option)==0){
				che = 1;
				while (1){
					int32_t check = 0;
					if (check ==0 && *(str+count) == ' ') fprintf(output, " ");
					else if (*(str+count)=='\n' || *(str+count) == '\0'){
						ind = 0;
						fprintf(output,"%s\n", value);
						count+=1;
						break;
					}else{
						*(com+ind) = *(str+count);
						ind+=1;
						check = 1;
					}
					count+=1;
				}
			}
		}else if (*(str+count) == '\n'){
			*(com+ind) = '\0';
			ind = 0;
			fprintf(output, "%s\n", com);
			count+=1;
		}else{
			*(com+ind) = *(str+count);
			ind+=1;
			count+=1;
		}
	}
	if (che==0) printf("Your option don't be found!\n");
	else printf("Done!\n");

	fclose(output);

	return 0;
}

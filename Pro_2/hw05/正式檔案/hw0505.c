#include <stdio.h>
#include <stdint.h>
#include <dirent.h>

int main(int32_t argc, char *argv[]){

    DIR *dp;
    struct dirent *dirp;
	int32_t count = 1;

    if (argc != 2) {
		printf("The command is \"$./hw0505 /etc\" (example)\n");
		return 0;
    }

    if ((dp = opendir(argv[1])) == NULL){
        printf("The dir can't be open %s", argv[1]);
		return 0;
	}

	printf("\tDIR FILENAME\n");

    while ((dirp=readdir(dp)) != NULL)
		printf("%d)\t%s\n", count++, dirp->d_name);

    closedir(dp);

    return 0;
}

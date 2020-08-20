#include <stdio.h>
#include <stdint.h>

int main(){

	int32_t type = 0;
	printf("Please enter the operation choice (1: add; 2: sub; 3: mul): ");
	scanf("%d", &type);

	while (!(type >= 1 && type <=3)){
		printf("Error message! (about your type isn't on [1,3])\n");
		printf("Please enter the operation choice (1: add; 2: sub; 3: mul): ");
		scanf("%d", &type);
	}

	int32_t x_size = 0, y_size = 0;
	printf("Please enter the sizeof the 1st matrix: ");
	scanf("%d %d", &x_size, &y_size);
	int32_t one_arr[x_size][y_size];
	for (int32_t i = 0 ; i < x_size; i++){
		printf("Please enter the ");
		if (i==0) printf("1st ");
		else if (i==1) printf("2nd ");
		else if (i==2) printf("3rd ");
		else printf("%dth ", i+1);
		printf("row of the 1st matrix (%d numbers): ", y_size);
		for (int32_t j=0; j<y_size; j++){
			scanf("%d", &one_arr[i][j]);
		}
	}

	int32_t x_size2 = 0, y_size2 = 0;
	printf("Please enter the sizeof the 2nd matrix: ");
	scanf("%d %d", &x_size2, &y_size2);
	while ((type ==1 || type ==2) && (!(x_size2==x_size && y_size2==y_size))){
		printf("Error! your type is add or sub, the two matrix should be same as\n");
		printf("Please enter the sizeof the 2nd matrix: ");
		scanf("%d %d", &x_size2, &y_size2);
	}
	int32_t two_arr[x_size2][y_size2];
	for (int32_t i = 0 ; i < x_size2; i++){
		printf("Please enter the ");
		if (i==0) printf("1st ");
		else if (i==1) printf("2nd ");
		else if (i==2) printf("3rd ");
		else printf("%dth ", i+1);
		printf("row of the 2nd matrix (%d numbers): ", y_size2);
		for (int32_t j=0; j<y_size2; j++){
			scanf("%d", &two_arr[i][j]);
		}
	}
	int32_t tran = 1;
	if (type==1 || type==2){
		if (type==2) tran = -1;
		if (x_size==x_size2 && y_size == y_size2){
			printf("Answer:\n");
			for (int32_t i = 0 ; i < x_size ; i++){
				for (int32_t j = 0 ; j < y_size; j++){
					printf("%d ", one_arr[i][j] + (two_arr[i][j])*tran);
				}
				puts("");
			}
		}else{
			printf("Error message! (about your two array size isn't same as)\n");
		}
	}else if (type == 3){
		if (y_size == x_size2){
			printf("Answer:\n");
			int32_t produ[x_size][y_size2];
			for (int32_t k = 0 ; k < x_size; k++){
				for (int32_t t = 0 ; t < y_size2; t++){
					produ[k][t] = 0;
					for (int32_t t2 = 0 ; t2< y_size; t2++){
						produ[k][t]+= (one_arr[k][t2] * two_arr[t2][t]);
					}
					printf("%d\t", produ[k][t]);
				}
				puts("");
			}

		}else{
			printf("Error message! (about your two array size don't product)\n");
		}

	}else{
		printf("Error message!\n");
	}

	return 0;
}

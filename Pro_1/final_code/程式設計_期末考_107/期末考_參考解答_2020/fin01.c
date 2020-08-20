#include <stdio.h>
#include <stdint.h>

int main(){

	int32_t check = 0;
	int32_t r = 0;
	int32_t n = 0 ;
	double ans = 0;

	printf("Please enter the resistance (1-100): ");
	scanf("%d", &check);
	while (!(check>=1 && check<=100)){
		printf("input error!");
		printf("PLease enter the resistance (1-100): ");
		scanf("%d", &check);
	}
	r= check;


	printf("Please enter n (1-100): ");
	scanf("%d", &check);
	while (!(check>=1 && check<=100)){
		printf("input error!");
		printf("Please enter n (1-100): ");
		scanf("%d", &check);
	}
	n = check;

	printf("Ans: ");
	if (n==1){
		printf("%d\n",2*r);
	}else{
		double tep = r;
		for (int32_t i = 0 ; i < n-1; i++){
			double r1 = tep+r;
			double r2 = r;
			double r3 = 1.0/((1.0/r1) + (1.0/r2));
			tep = r3;
		}
		tep+=r;
		printf("%lf\n", tep);

	}


}

//解釋請見README第六題

#include <stdio.h>
#include <stdint.h>

int p(int i, int N) {
	return (i < N && printf("%d\n", i) && !p(i + 1, N)) || printf("%d\n", i);
}

int main(){

	int i = 0 , N = 0;

	printf("Please enter two integer: ");
	scanf("%d %d", &i, &N);
	printf("%d\n", p(i,N));

	return 0;
}

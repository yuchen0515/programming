#include "test.h"

int32_t fibonacci(int32_t n){
	if (n <= 1) return n;
	return fibonacci(n - 1) + fibonacci(n - 2);
}

int32_t factorial(int32_t n){
	int32_t result = 1;
	for (int32_t i = 1 ; i <= n ; i++){
		result*= i;
	}
	return result;
}

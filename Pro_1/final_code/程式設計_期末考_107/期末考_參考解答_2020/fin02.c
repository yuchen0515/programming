#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include "maze.h"

int32_t maze(int32_t array[m][n], int32_t row, int32_t col, int32_t pos[m*m][2],int32_t count);
int32_t ma(int32_t array[m][n], int32_t row, int32_t col, int32_t pos[m*m][2], int32_t count, int32_t roworcol, int32_t num){
	
		array[row][col]=2;
		pos[count][0] = row; pos[count][1] = col;
		int32_t temp= 0;
		if (roworcol==0) temp = maze(array, row+num, col, pos, count+1);
		else if (roworcol==1) temp = maze(array, row, col+num, pos, count+1);

		if (temp!=-1) return temp;
		pos[count][0] = 0; pos[count][1] = 0;
		array[row][col]=0;

		return -1;
}

int32_t maze(int32_t array[m][n], int32_t row, int32_t col, int32_t pos[m*m][2],int32_t count){

	if (row==m-1 && col==n-1) return count;
	int32_t temp = 0;

	if (row!=0){
		if (!(array[row-1][col])){
			temp = ma(array, row, col, pos, count, 0, -1);
			if (temp!=-1) return temp;
		}
	}
	if (row!=m-1){
		if (!(array[row+1][col])){
			temp = ma(array, row, col, pos, count, 0, 1);
			if (temp!=-1) return temp;
		}
	}
	if (col!=0){
		if (!(array[row][col-1])){
			temp = ma(array, row, col, pos, count, 1, -1);
			if (temp!=-1) return temp;
		}
	}
	if (col!=n-1){
		if (!(array[row+1][col])){
			temp = ma(array, row, col, pos, count, 1, 1);
			if (temp!=-1) return temp;
		}
	}
	return -1;

}

int main(){

	int32_t pos[m*n+1][2];
	for (int32_t i = 0 ; i < m*n+1; i++){
		for (int32_t j = 0; j < 2; j++){
			pos[i][j] = 0;
		}
	}

	int32_t index = maze(array, 0, 0, pos, 0);
	pos[index][0]=m-1; pos[index][1]=n-1;

	for (int32_t i = 0 ; i < index+1; i++){
		system("clear");
		for (int32_t j = 0; j < n+2; j++){
			printf("+");
		}
		puts("");
		for (int32_t j = 0 ; j < m ; j++){
			printf("+");
			for (int32_t k = 0; k < n; k++){
				if (j == pos[i][0] && k==pos[i][1]){
					printf("*");
				}else if (array[j][k]==1){
					printf("+");
				}else if (array[j][k]==2 || array[j][k]==0){
					printf(" ");
				}
			}
			printf("+");
			puts("");
		}
		for (int32_t j = 0; j < n+2; j++){
			printf("+");
		}
		puts("");
		if (i == index) printf("EXIT\n");
		usleep(1000*200);

	}
	

}

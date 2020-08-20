#include "final.h"

// Problem 01: Matrix Operation

int32_t dim2todim1(int32_t entryi, int32_t entryj, int32_t column){
	return entryi*column+entryj;
}

void addMatrix( int32_t output[], int32_t oprand1[], int32_t operand2[], int32_t row, int32_t column )
{
	for (int32_t i=0; i < row; i++){
		for (int32_t j = 0 ; j < column; j++){
			int32_t temp = dim2todim1(i,j,column);
			output[temp] = oprand1[temp] + operand2[temp];
		}
	}

    return;
}

void subMatrix( int32_t output[], int32_t oprand1[], int32_t operand2[], int32_t row, int32_t column )
{
	for (int32_t i=0; i < row; i++){
		for (int32_t j = 0 ; j < column; j++){
			int32_t temp = dim2todim1(i,j,column);
			output[temp] = oprand1[temp] - operand2[temp];
		}
	}
    return;
}

int32_t mulMatrix( int32_t output[], int32_t oprand1[], int32_t row1, int32_t column1, int32_t operand2[], int32_t row2, int32_t column2 )
{
	for (int32_t i = 0 ; i < row1; i++){
		for (int32_t j = 0 ; j < column2; j++){
			int32_t out_temp = dim2todim1(i,j,column2);
			int32_t sum_temp = 0;
			for (int32_t p = 0 ; p < column1; p++){
				int32_t opr1_temp = dim2todim1(i,p,column1);
				int32_t opr2_temp = dim2todim1(p,j,column2);
				sum_temp += (oprand1[opr1_temp] * operand2[opr2_temp]);
			}
			output[out_temp] = sum_temp;
		}
	}
    return 0;
}

void tpMatrix ( int32_t output[], int32_t oprand1[], int32_t row, int32_t column )
{
	for (int32_t i=0; i < row; i++){
		for (int32_t j = 0 ; j < column; j++){
			int32_t temp = dim2todim1(i,j,column);
			int32_t temp2 = dim2todim1(j,i,column);
			output[temp2] = oprand1[temp];
		}
	}

    return;
}

// Problem 02: Sorting Two Arrays

void sortTwoArray01( int32_t output[], int32_t array01[], int32_t size01, int32_t array02[], int32_t size02 )
{
	for (int32_t i = 0 ; i < size01 ; i ++){
		output[i] = array01[i];
	}
	for (int32_t i = size01 ; i < (size01+size02); i++){
		output[i] = array02[i-size01];
	}
	int32_t temp = size01+size02;
	for (int32_t i = 0 ; i < temp; i++){
		for (int32_t j = 1 ; j < temp-i ; j ++){
			if (output[j-1] < output[j]){
				int32_t temp_ou = output[j-1];
				output[j-1] = output[j];
				output[j] = temp_ou;
			}
		}
	}

    return;
}

void sortTwoArray02( int32_t **ppOutput, int32_t array01[], int32_t size01, int32_t array02[], int32_t size02 )
{
	int32_t temp = size01+size02;
	int32_t *ptr = calloc(sizeof(int32_t), temp); 
	*ppOutput = ptr;

	for (int32_t i = 0 ; i < size01 ; i ++){
		*(*ppOutput+i) = array01[i];
	}
	for (int32_t i = size01 ; i < (size01+size02); i++){
		*(*ppOutput+i) = array02[i-size01];
	}
	for (int32_t i = 0 ; i < temp; i++){
		for (int32_t j = 1 ; j < temp-i ; j ++){
			if (*(*ppOutput+j-1) > *(*ppOutput+j)){
				int32_t temp_ou = *(*ppOutput+j-1);
				*(*ppOutput+j-1) = *(*ppOutput+j);
				*(*ppOutput+j) = temp_ou;
			}
		}
	}
    return;
}

int32_t compare(int32_t a, int32_t b){
	if (a%13==0 && b%13==0){
		if (a/13 < b/13) return 1;
	}else if (a%13!=0 && b%13==0){
		return 1;
	}else if (a%13!=0 && b%13!=0){
		if (a<b)	return 1;
	}
	return 0;

}

void sortTwoArray03( int32_t output[], int32_t array01[], int32_t size01, int32_t array02[], int32_t size02 )
{
	for (int32_t i = 0 ; i < size01 ; i ++){
		output[i] = array01[i];
	}
	for (int32_t i = size01 ; i < (size01+size02); i++){
		output[i] = array02[i-size01];
	}
	int32_t temp = size01+size02;
	for (int32_t i = 0 ; i < temp; i++){
		for (int32_t j = 1 ; j < temp-i ; j ++){
			if (compare(output[j-1],output[j])){
				int32_t temp_ou = output[j-1];
				output[j-1] = output[j];
				output[j] = temp_ou;
			}
		}
	}
    return;
}

// Problem 03: String to Number

int32_t len(char *pStr){
	int32_t le = 0;
	while (*(pStr + le)){
		le++;
	}
	return le;
}

void myAtoi( char *pStr, uint32_t *pResult )
{
	for (int32_t i = 0 ; i < len(pStr) ; i++){
		*pResult *=10;
		*pResult += *(pStr+i)-'0';
	}
    return;
}

void myAtol( char *pStr, uint64_t *pResult )
{
	for (int32_t i = 0 ; i < len(pStr) ; i++){
		*pResult *=10;
		*pResult += *(pStr+i)-'0';
	}
    return;
}

uint32_t upper(uint32_t temp){
	uint32_t tep = temp;
	uint32_t len = 0 ;
	while (tep/10 >0){
		tep = tep/10;
		len = tep%10;
	}
	return len;

}

int32_t shift512(uint32_t result[16], uint32_t index, uint32_t num){
	uint32_t temp = result[index];
	if (index==0){
		result[index]*=10;
		result[index]+=num;
	}
	if (result[index]/10 != temp && index==15) return -1;
	else if (result[index]/10!=temp){
		//result[index+1] += upper(temp);
		if (temp >= 858993459) result[index+1]+=1;	
		result[index+1] +=1;
		if (index!=0 && index!=14){
			if (result[index+1] ==0){
				result[index+2] +=1;
			}
		}else if (index==14){
			if (result[index+1]==0) return -1;
		}
	}
	return 1;
}

// Binus: If the value of the input string isover 512 bits, return -1.
int32_t myAto512( char *pStr, uint32_t result[16] )
{
	int32_t leng = len(pStr);
	uint32_t temp = 0;
	

	for (int32_t i = 0 ; i < leng ; i++){
		temp = *(pStr+i)-'0';
		for (int32_t j = 15 ; j >=0 ; j--){
			int32_t tep = shift512(result, j, temp);
			if (tep==-1){
				printf("%d\t", tep);
				return -1;
			}
		}
	}


    return 0;
} 

// Problem 04: Sudoku Solver 

static int32_t isValid( int32_t number, int32_t puzzle[9][9], int32_t row, int32_t column ) 
{
    int32_t sectorRow = 3 * ( row/3 );
    int32_t sectorCol = 3 * ( column/3 );
    int32_t row1 = ( row + 2 )%3;
    int32_t row2 = ( row + 4 )%3;
    int32_t col1 = ( column + 2 ) % 3;
    int32_t col2 = ( column + 4 ) % 3;
 
    /* Check for the value in the given row and column */
    for ( int32_t i = 0; i < 9; i++ ) 
    {
        if ( puzzle[i][column] == number ) return 0;
        if ( puzzle[row][i] == number ) return 0;
    }
 
    /* Check the remaining four spaces in this sector */
    if( puzzle[row1+sectorRow][col1+sectorCol] == number ) return 0;
    if( puzzle[row2+sectorRow][col1+sectorCol] == number ) return 0;
    if( puzzle[row1+sectorRow][col2+sectorCol] == number ) return 0;
    if( puzzle[row2+sectorRow][col2+sectorCol] == number ) return 0;
    return 1;
}

void pri_arr(int32_t puzzle[9][9]){
	for (int32_t i = 0 ; i < 9 ; i ++){
		for (int32_t j = 0 ; j < 9 ; j++){
			printf("%d ", puzzle[i][j]);
		}
		puts("");
	}
}

void copy_arr(int32_t puzzle[9][9], int32_t copy[9][9]){
	for (int32_t i = 0 ; i < 9 ; i ++){
		for (int32_t j = 0 ; j < 9 ; j++){
			copy[i][j] = puzzle[i][j];
		}
	}
}

// 0 means fail, 1 means pass
static int32_t sudokuSolver( int32_t puzzle[9][9], int32_t row, int32_t column ) 
{
	int32_t temp = 0;
	if (row==9 && column ==0) return 1;
 	if (column==9){
		temp =sudokuSolver(puzzle, row+1,0);
		if (temp==1) return 1;
	}
	if (puzzle[row][column]!=0){
		temp = sudokuSolver(puzzle, row, column+1);
		if (temp==1) return 1;

		return 0;
	}
	//int32_t puz[9][9];
	int32_t arr[9]= {0};
	//copy_arr(puzzle, puz);
	int32_t j = 0 ;
	for (int32_t i = 1 ; i < 10 ; i++){
		if (isValid(i, puzzle, row, column)){
			arr[j++] = i;
		}
	}
	if (arr[0]==0) return 0;

	for (int32_t i = 0 ; i < 9; i ++){
		if (arr[i]!=0){
			puzzle[row][column] = arr[i];
			temp = sudokuSolver(puzzle, row, column+1);
			if (temp==1) return 1;
			puzzle[row][column] = 0;
		}else break;
	}
    
    /*
    * Implement this function here.
    */
	if (temp == 1) return 1;

    return 0;
}

int32_t playSudoku( int32_t puzzle[9][9] )
{
    /*
    * Hint:
    * You can use the recursive approach.
    * sudokuSolver can be implemented as a recursive function.
    * The template of sudoku is given before this function.
    * If you want to use this approach, uncomment the following line.
    * Of course, you can use your own solution.
    * The recursive way is easy. You should call sudokuSolver( puzzle, m, n+1 ) in sudokuSolver.
    * When n+1 == 9, call sudokuSolver( puzzle, m+1, 0 ) 
    */
     return sudokuSolver( puzzle, 0, 0 );
    //return 0;
}

// Bonus: Binary Complement
int32_t bin_len(int32_t input){
	int32_t len = 0;
	while (input){
		input = input>>1;
		len++;
	}
	return len;
}

void bin_arr(int32_t temp, int32_t bin[], int32_t len){

	for (int32_t i = 0 ; i < len ; i++){
		if (temp%2==0) *(bin+i)=0;	
		else if (temp%2==1) *(bin+i)=1;
		temp >>=1;
	}

}

void one_complement(int32_t bin[], int32_t len){

	for (int32_t i = 0 ; i < len ; i++){
		*(bin+i) = !(*(bin+i));
	}

}

void bin_carry(int32_t bin[], int32_t len){

	for (int32_t i = 0 ; i < len ; i++){
		if (*(bin+i) ==2){
			*(bin+i)==0;
			if (i!=len-1) *(bin+i+1)+=1;
		}else break;
	}

}

int32_t bin_to_dec(int32_t bin[], int32_t len){

	int32_t pow_ = 1;
	int32_t ret = 0;
	for (int32_t i = 0 ; i < len ; i++){
		ret+=(*(bin+i) * pow_);
		pow_<<=1;
	}

	return ret;
}

int32_t binComplement( int32_t input )
{
	int32_t len = bin_len(input);
	int32_t *ptr = calloc(sizeof(int32_t), len);

	bin_arr(input, ptr, len);
	one_complement(ptr, len);
	*(ptr)+=1;
	bin_carry(ptr, len);

    return bin_to_dec(ptr, len);
}

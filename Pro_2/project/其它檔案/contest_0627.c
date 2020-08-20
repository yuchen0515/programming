#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

typedef struct _sPlayer
{
    int32_t     id;
    int32_t     score;
    void        ( *setup )( int32_t id );
    void        ( *deal )( const int32_t card[10] );
    int32_t     ( *pick )( const int32_t table[4][5], const int32_t score[2], const int32_t last[8], const int32_t card[10] );
    int32_t     ( *choose )( const int32_t table[4][5], int32_t card );
} sPlayer;  

#define NUMBER (70)

// A utility function to swap to integers 
void swap (int32_t *a, int32_t *b) 
{ 
    int32_t temp = *a; 
    *a = *b; 
    *b = temp; 
} 

// A function to generate a random permutation of arr[] 
void shuffle( int arr[], int n ) 
{ 
    // Use a different seed value so that we don't get same 
    // result each time we run this program 
    srand ( time(NULL) ); 
  
    // Start from the last element and swap one by one. We don't 
    // need to run for the first element that's why i > 0 
    for (int i = n-1; i > 0; i--) 
    { 
        // Pick a random index from 0 to i 
        int j = rand() % (i+1); 
  
        // Swap arr[i] with the element at random index 
        swap( &arr[i], &arr[j] ); 
    } 
} 

//誰是牛頭王的規則計分
int32_t count(int32_t number)
{
	//point:牛頭數量
	int32_t point;	
	switch(number)
	{
		case 55:
			point = 7;
			break;
		case 11: case 22: case 33: case 44: case 66: case 77: case 88: case 99:
			point = 5;
			break;
		case 10: case 20: case 30: case 40: case 50: case 60: case 70: case 80: case 90: case 100:
			point = 3;
			break;
		case 5: case 15: case 25: case 35: case 45: case 65: case 75: case 85: case 95:
			point = 2;
			break;
		default:
			point = 1;
			break;
	}	
	return point;
}

int main()
{
    sPlayer player[NUMBER];
    
    // Register all functions for all students
    player[0].id = 0;
    player[0].score = 0;
    player[0].setup = CSIE_ID_setup;
    player[0].deal = CSIE_ID_deal;
    player[0].choose = CSIE_ID_choose;

	//計分版
    int32_t win[NUMBER][NUMBER];
	for(int32_t x = 0; x<NUMBER ; x++)	
		memset(win[x],0,NUMBER);    
	
	FILE *output;
	output = fopen("6Nimmt!_fight.txt","a");
	
    // All Contest Runs, i vs. j
    for( int32_t i = 0 ; i < NUMBER - 1 ; i++ )
    {
        for( int32_t j = i + 1 ; j < NUMBER ; j++ )
        {
        	fprintf(output,"%d\tVs\t%d\n",i,j);
			//可先當作奇數場
            // 1000 Runs
            for( int32_t k = 0 ; k < 1000 ; k++ )
            {
                // Initialization
                player[i].setup( 0 );
                player[j].setup( 1 );
                
                int32_t score[2] = {0};
                
                // Shuffle
                
                int32_t cards[104] = {0};
                
                for( int32_t l = 0 ; l < 104 ; l++ )
                {
                    cards[l] = l + 1;
                }
                
                shuffle( cards, 104 );
                
                // Deal
                int32_t card0[10] = {0};
                int32_t card1[10] = {0};
                
                for( int32_t l = 0 ; l < 10 ; l++ )
                {
                    card0[l] = cards[2 * l];
                    card1[l] = cards[2 * l + 1];
                }
                
                int32_t table[4][5] = {0};
                
                table[0][0] = cards[20];
                table[1][0] = cards[21];
                table[2][0] = cards[22];
                table[3][0] = cards[23];
                
				//方便系統判別當前牌堆大小
				//牌堆大小由小到大 0-3, 0最小3最大
                for( int32_t x = 0 ; x < 3 ; x++)
 				{
 					int32_t banner , min = table[x][0];
                	for( int32_t y = x+1 ; y < 4; y++)
                	{
                		if(min > table[y][0])
                		{
                			min = table[y][0];
							banner = y;
						}
                	}
                	table[banner][0] = table[x][0];
                	table[x][0] = min;
				}
				
				int32_t last0[8] = {0} , last1[8] = {0} , flag[4] = {0};
                
                player[i].deal( card0 ); 
                player[j].deal( card1 ); 
                
                // Play
                for( int32_t l = 0 ; l < 10 ; l++ )
                {
                	int32_t value[2];
					value[0] = player[i].pick( table , player[i].score[0] , last1, card0 ); 
            		value[1] = player[j].pick( table , player[j].score[1] , last0, card1 );
            		
					last0[l] = value[0];
            		last1[l] = value[1];
					
					//i player's card is smaller than j player's card
					if(value[0] < value[1])
					{
						//game process for player[i]'s card
						//當卡片大小小於四個牌堆
						if(value[0] < table[0][flag[0]-1]) 
						{
							//玩家選擇一個牌堆拿走
							int32_t a = player[i].choose( table , value[0]);
							//計算此牌堆牛頭數量
							for( int32_t x = 0 ; x < flag[a] ; x++)				
								player[i].score += count( table[a][x]);
							//reset牌堆
							memset(table[a] , 0 , 5);
							//將卡片放入此牌堆
							table[a][0] = value[0];		
							flag[a] = 1;
							
							//方便系統判別當前牌堆大小
							//牌堆大小由小到大0-3, 0最小3最大
							for( int32_t x = 0 ; x < 3 ; x++)
			 				{
			 					int32_t banner , min = table[x][flag[x]-1];
			                	for( int32_t y = x+1 ; y < 4; y++)
			                	{
			                		if(min > table[y][flag[y]-1])
			                		{
			                			min = table[y][flag[y]-1];
										banner = y;
									}
			                	}
			                	for( int32_t z = 0 ; z < 5 ; z++)
			                	{
			                		int32_t reg = table[banner][z];
			                		table[banner][z] = table[x][z];
			                		table[x][z] = reg;
			                		
			                		reg = flag[banner];
			                		flag[banner] = flag[x];
			                		flag[x] = reg;
			                	}
							}
						}	
						else
						{
							//當卡片大小小於table[3]
							if(value[0] > table[3][flag[3]-1])
							{
								//當牌堆達到上限
								if(flag[3] == 5)
								{
									//計算此牌堆牛頭數量
									for( int32_t x = 0 ; x < flag[3] ; x++)
										player[i].score += count( table[3][x] );
									//reset牌堆
									memset( table[3] , 0 , 5);
									//將卡片放入此牌堆
									table[3][0] = value[0];
									flag[3] = 1;
								}
								//牌堆未達上限
								else					
								{
									//卡片放入此牌堆
									table[3][flag[3]] = value[0];
									flag[3]++;
								}
							}
							else if(value[0] > table[2][flag[2]-1])				//·í¥d¤ù¤j¤p¤j©ótable[2]
							{
								if(flag[2] == 5)								//·íµP°ï¹F¨ì¤W­­ 
								{
									for( int32_t x = 0 ; x < flag[2] ; x++)		//­pºâ¦¹µP°ï¤ûÀY¼Æ¶q
										player[i].score += count( table[2][x] );
									memset( table[2] , 0 , 5);					//resetµP°ï 
									table[2][0] = value[0];						//±N¥d¤ù©ñ¤J¦¹µP°ï 
									flag[2] = 1;
								}
								else											//µP°ï¥¼¹F¤W­­
								{
									table[2][flag[2]] = value[0];				//¥d¤ù©ñ¤J¦¹µP°ï
									flag[2]++;
								}
							}
							else if(value[0] > table[1][flag[1]-1])				//·í¥d¤ù¤j¤p¤j©ótable[1]
							{
								if(flag[1] == 5)								//·íµP°ï¹F¨ì¤W­­
								{
									for( int32_t x = 0 ; x < flag[1] ; x++)		//­pºâ¦¹µP°ï¤ûÀY¼Æ¶q
										player[i].score += count( table[1][x]);
									memset( table[1] , 0 , 5);					//resetµP°ï
									table[1][0] = value[0];						//±N¥d¤ù©ñ¤J¦¹µP°ï
									flag[1] = 1;
								}
								else											//µP°ï¥¼¹F¤W­­
								{
									table[1][flag[1]] = value[0];				//¥d¤ù©ñ¤J¦¹µP°ï
									flag[1]++;
								}
							}
							else												//·í¥d¤ù¤j¤p¤j©ótable[0]
							{
								if(flag[0] == 5)								//·íµP°ï¹F¨ì¤W­­
								{
									for( int32_t x = 0 ; x < flag[0] ; x++)		//­pºâ¦¹µP°ï¤ûÀY¼Æ¶q
										player[i].score += count( table[0][x]);	
									memset( table[0] , 0 , 5);					//resetµP°ï
									table[0][0] = value[0];						//±N¥d¤ù©ñ¤J¦¹µP°ï
									flag[0] = 1;
								}
								else											//µP°ï¥¼¹F¤W­­
								{
									table[0][flag[0]] = value[0];				//¥d¤ù©ñ¤J¦¹µP°ï
									flag[0]++;
								}
							}
							
							//¤è«K¨t²Î§P§O·í«eµP°ï¤j¤p µP°ï¤j¤p¥Ñ¤p¨ì¤j0-3 0³Ì¤p3³Ì¤j
							for( int32_t x = 0 ; x < 3 ; x++)
			 				{
			 					int32_t banner , min = table[x][flag[x]-1];
			                	for( int32_t y = x+1 ; y < 4; y++)
			                	{
			                		if(min > table[y][flag[y]-1])
			                		{
			                			min = table[y][flag[y]-1];
										banner = y;
									}
			                	}
			                	for( int32_t z = 0 ; z < 5 ; z++)
			                	{
			                		int32_t reg = table[banner][z];
			                		table[banner][z] = table[x][z];
			                		table[x][z] = reg;
			                		
			                		reg = flag[banner];
			                		flag[banner] = flag[x];
			                		flag[x] = reg;
			                	}
							}
						}
						//game process for player[j]'s card
						if(value[1] < table[0][flag[0]-1]) 						//·í¥d¤ù¤j¤p¤p©ó¥|­ÓµP°ï
						{
							int32_t a = player[j].choose( table , value[1]);	//ª±®a¿ï¾Ü¤@­ÓµP°ï®³¨« 
							for( int32_t x = 0 ; x < flag[a] ; x++)				//­pºâ¦¹µP°ï¤ûÀY¼Æ¶q
								player[j].score += count( table[a][x]);			
							memset(table[a] , 0 , 5);						 	//resetµP°ï
							table[a][0] = value[0];								//±N¥d¤ù©ñ¤J¦¹µP°ï
							flag[a] = 1;
							
							//¤è«K¨t²Î§P§O·í«eµP°ï¤j¤p µP°ï¤j¤p¥Ñ¤p¨ì¤j0-3 0³Ì¤p3³Ì¤j
							for( int32_t x = 0 ; x < 3 ; x++)
			 				{
			 					int32_t banner , min = table[x][flag[x]-1];
			                	for( int32_t y = x+1 ; y < 4; y++)
			                	{
			                		if(min > table[y][flag[y]-1])
			                		{
			                			min = table[y][flag[y]-1];
										banner = y;
									}
			                	}
			                	for( int32_t z = 0 ; z < 5 ; z++)
			                	{
			                		int32_t reg = table[banner][z];
			                		table[banner][z] = table[x][z];
			                		table[x][z] = reg;
			                		
			                		reg = flag[banner];
			                		flag[banner] = flag[x];
			                		flag[x] = reg;
			                	}
							}
						}	
						else
						{
							if(value[1] > table[3][flag[3]-1])					//·í¥d¤ù¤j¤p¤j©ótable[3]
							{
								if(flag[3] == 5)								//·íµP°ï¹F¨ì¤W­­
								{
									for( int32_t x = 0 ; x < flag[3] ; x++)		//­pºâ¦¹µP°ï¤ûÀY¼Æ¶q
										player[j].score += count( table[3][x] );
									memset( table[3] , 0 , 5);					//resetµP°ï
									table[3][0] = value[1];						//±N¥d¤ù©ñ¤J¦¹µP°ï
									flag[3] = 1;
								}
								else											//µP°ï¥¼¹F¤W­­
								{
									table[3][flag[3]] = value[1];				//¥d¤ù©ñ¤J¦¹µP°ï
									flag[3]++;
								}
							}
							else if(value[1] > table[2][flag[2]-1])				//·í¥d¤ù¤j¤p¤j©ótable[2]
							{
								if(flag[2] == 5)								//·íµP°ï¹F¨ì¤W­­
								{
									for( int32_t x = 0 ; x < flag[2] ; x++)		//­pºâ¦¹µP°ï¤ûÀY¼Æ¶q
										player[j].score += count( table[2][x] );
									memset( table[2] , 0 , 5);					//resetµP°ï
									table[2][0] = value[1];						//±N¥d¤ù©ñ¤J¦¹µP°ï
									flag[2] = 1;
								}
								else											//µP°ï¥¼¹F¤W­­
								{
									table[2][flag[2]] = value[1];				//¥d¤ù©ñ¤J¦¹µP°ï
									flag[2]++;
								}
							}
							else if(value[1] > table[1][flag[1]-1])				//·í¥d¤ù¤j¤p¤j©ótable[1]
							{
								if(flag[1] == 5)								//·íµP°ï¹F¨ì¤W­­
								{
									for( int32_t x = 0 ; x < flag[1] ; x++)		//­pºâ¦¹µP°ï¤ûÀY¼Æ¶q
										player[j].score += count( table[1][x]);
									memset( table[1] , 0 , 5);					//resetµP°ï
									table[1][0] = value[1];						//±N¥d¤ù©ñ¤J¦¹µP°ï
									flag[1] = 1;
								}
								else											//µP°ï¥¼¹F¤W­­
								{
									table[1][flag[1]] = value[1];				//¥d¤ù©ñ¤J¦¹µP°ï
									flag[1]++;
								}
							}
							else												//·í¥d¤ù¤j¤p¤j©ótable[0]
							{
								if(flag[0] == 5)								//·íµP°ï¹F¨ì¤W­­
								{
									for( int32_t x = 0 ; x < flag[0] ; x++)		//­pºâ¦¹µP°ï¤ûÀY¼Æ¶q
										player[j].score += count( table[0][x]);
									memset( table[0] , 0 , 5);					//resetµP°ï
									table[0][0] = value[1];						//±N¥d¤ù©ñ¤J¦¹µP°ï
									flag[0] = 1;
								}
								else											//µP°ï¥¼¹F¤W­­
								{
									table[0][flag[0]] = value[1];				//¥d¤ù©ñ¤J¦¹µP°ï
									flag[0]++;
								}
							}
							
							//¤è«K¨t²Î§P§O·í«eµP°ï¤j¤p µP°ï¤j¤p¥Ñ¤p¨ì¤j0-3 0³Ì¤p3³Ì¤j
							for( int32_t x = 0 ; x < 3 ; x++)
			 				{
			 					int32_t banner , min = table[x][flag[x]-1];
			                	for( int32_t y = x+1 ; y < 4; y++)
			                	{
			                		if(min > table[y][flag[y]-1])
			                		{
			                			min = table[y][flag[y]-1];
										banner = y;
									}
			                	}
			                	for( int32_t z = 0 ; z < 5 ; z++)
			                	{
			                		int32_t reg = table[banner][z];
			                		table[banner][z] = table[x][z];
			                		table[x][z] = reg;
			                		
			                		reg = flag[banner];
			                		flag[banner] = flag[x];
			                		flag[x] = reg;
			                	}
							}
						}	
					}
					else
					{
						//game process for player[j]'s card
						if(value[1] < table[0][flag[0]-1]) 						//·í¥d¤ù¤j¤p¤p©ó¥|­ÓµP°ï
						{
							int32_t a = player[j].choose( table , value[1]);	//ª±®a¿ï¾Ü¤@­ÓµP°ï®³¨« 
							for( int32_t x = 0 ; x < flag[a] ; x++)				//­pºâ¦¹µP°ï¤ûÀY¼Æ¶q
								player[j].score += count( table[a][x]);			
							memset(table[a] , 0 , 5);						 	//resetµP°ï
							table[a][0] = value[0];								//±N¥d¤ù©ñ¤J¦¹µP°ï
							flag[a] = 1;
							
							//¤è«K¨t²Î§P§O·í«eµP°ï¤j¤p µP°ï¤j¤p¥Ñ¤p¨ì¤j0-3 0³Ì¤p3³Ì¤j
							for( int32_t x = 0 ; x < 3 ; x++)
			 				{
			 					int32_t banner , min = table[x][flag[x]-1];
			                	for( int32_t y = x+1 ; y < 4; y++)
			                	{
			                		if(min > table[y][flag[y]-1])
			                		{
			                			min = table[y][flag[y]-1];
										banner = y;
									}
			                	}
			                	for( int32_t z = 0 ; z < 5 ; z++)
			                	{
			                		int32_t reg = table[banner][z];
			                		table[banner][z] = table[x][z];
			                		table[x][z] = reg;
			                		
			                		reg = flag[banner];
			                		flag[banner] = flag[x];
			                		flag[x] = reg;
			                	}
							}
						}	
						else
						{
							if(value[1] > table[3][flag[3]-1])					//·í¥d¤ù¤j¤p¤j©ótable[3]
							{
								if(flag[3] == 5)								//·íµP°ï¹F¨ì¤W­­
								{
									for( int32_t x = 0 ; x < flag[3] ; x++)		//­pºâ¦¹µP°ï¤ûÀY¼Æ¶q
										player[j].score += count( table[3][x] );
									memset( table[3] , 0 , 5);					//resetµP°ï
									table[3][0] = value[1];						//±N¥d¤ù©ñ¤J¦¹µP°ï
									flag[3] = 1;
								}
								else											//µP°ï¥¼¹F¤W­­
								{
									table[3][flag[3]] = value[1];				//¥d¤ù©ñ¤J¦¹µP°ï
									flag[3]++;
								}
							}
							else if(value[1] > table[2][flag[2]-1])				//·í¥d¤ù¤j¤p¤j©ótable[2]
							{
								if(flag[2] == 5)								//·íµP°ï¹F¨ì¤W­­
								{
									for( int32_t x = 0 ; x < flag[2] ; x++)		//­pºâ¦¹µP°ï¤ûÀY¼Æ¶q
										player[j].score += count( table[2][x] );
									memset( table[2] , 0 , 5);					//resetµP°ï
									table[2][0] = value[1];						//±N¥d¤ù©ñ¤J¦¹µP°ï
									flag[2] = 1;
								}
								else											//µP°ï¥¼¹F¤W­­
								{
									table[2][flag[2]] = value[1];				//¥d¤ù©ñ¤J¦¹µP°ï
									flag[2]++;
								}
							}
							else if(value[1] > table[1][flag[1]-1])				//·í¥d¤ù¤j¤p¤j©ótable[1]
							{
								if(flag[1] == 5)								//·íµP°ï¹F¨ì¤W­­
								{
									for( int32_t x = 0 ; x < flag[1] ; x++)		//­pºâ¦¹µP°ï¤ûÀY¼Æ¶q
										player[j].score += count( table[1][x]);
									memset( table[1] , 0 , 5);					//resetµP°ï
									table[1][0] = value[1];						//±N¥d¤ù©ñ¤J¦¹µP°ï
									flag[1] = 1;
								}
								else											//µP°ï¥¼¹F¤W­­
								{
									table[1][flag[1]] = value[1];				//¥d¤ù©ñ¤J¦¹µP°ï
									flag[1]++;
								}
							}
							else												//·í¥d¤ù¤j¤p¤j©ótable[0]
							{
								if(flag[0] == 5)								//·íµP°ï¹F¨ì¤W­­
								{
									for( int32_t x = 0 ; x < flag[0] ; x++)		//­pºâ¦¹µP°ï¤ûÀY¼Æ¶q
										player[j].score += count( table[0][x]);
									memset( table[0] , 0 , 5);					//resetµP°ï
									table[0][0] = value[1];						//±N¥d¤ù©ñ¤J¦¹µP°ï
									flag[0] = 1;
								}
								else											//µP°ï¥¼¹F¤W­­
								{
									table[0][flag[0]] = value[1];				//¥d¤ù©ñ¤J¦¹µP°ï
									flag[0]++;
								}
							}
							
							//¤è«K¨t²Î§P§O·í«eµP°ï¤j¤p µP°ï¤j¤p¥Ñ¤p¨ì¤j0-3 0³Ì¤p3³Ì¤j
							for( int32_t x = 0 ; x < 3 ; x++)
			 				{
			 					int32_t banner , min = table[x][flag[x]-1];
			                	for( int32_t y = x+1 ; y < 4; y++)
			                	{
			                		if(min > table[y][flag[y]-1])
			                		{
			                			min = table[y][flag[y]-1];
										banner = y;
									}
			                	}
			                	for( int32_t z = 0 ; z < 5 ; z++)
			                	{
			                		int32_t reg = table[banner][z];
			                		table[banner][z] = table[x][z];
			                		table[x][z] = reg;
			                		
			                		reg = flag[banner];
			                		flag[banner] = flag[x];
			                		flag[x] = reg;
			                	}
							}
						}	
						//game process for player[i]'s card
						if(value[0] < table[0][flag[0]-1]) 						//·í¥d¤ù¤j¤p¤p©ó¥|­ÓµP°ï 
						{
							int32_t a = player[i].choose( table , value[0]);	//ª±®a¿ï¾Ü¤@­ÓµP°ï®³¨« 
							for( int32_t x = 0 ; x < flag[a] ; x++)				//­pºâ¦¹µP°ï¤ûÀY¼Æ¶q 
								player[i].score += count( table[a][x]);
							memset(table[a] , 0 , 5);							//resetµP°ï 
							table[a][0] = value[0];								//±N¥d¤ù©ñ¤J¦¹µP°ï 
							flag[a] = 1;
							
							//¤è«K¨t²Î§P§O·í«eµP°ï¤j¤p µP°ï¤j¤p¥Ñ¤p¨ì¤j0-3 0³Ì¤p3³Ì¤j 
							for( int32_t x = 0 ; x < 3 ; x++)
			 				{
			 					int32_t banner , min = table[x][flag[x]-1];
			                	for( int32_t y = x+1 ; y < 4; y++)
			                	{
			                		if(min > table[y][flag[y]-1])
			                		{
			                			min = table[y][flag[y]-1];
										banner = y;
									}
			                	}
			                	for( int32_t z = 0 ; z < 5 ; z++)
			                	{
			                		int32_t reg = table[banner][z];
			                		table[banner][z] = table[x][z];
			                		table[x][z] = reg;
			                		
			                		reg = flag[banner];
			                		flag[banner] = flag[x];
			                		flag[x] = reg;
			                	}
							}
						}	
						else
						{
							if(value[0] > table[3][flag[3]-1]) 					//·í¥d¤ù¤j¤p¤j©ótable[3] 
							{
								if(flag[3] == 5)								//·íµP°ï¹F¨ì¤W­­ 
								{
									for( int32_t x = 0 ; x < flag[3] ; x++)		//­pºâ¦¹µP°ï¤ûÀY¼Æ¶q
										player[i].score += count( table[3][x] );
									memset( table[3] , 0 , 5);					//resetµP°ï 
									table[3][0] = value[0];						//±N¥d¤ù©ñ¤J¦¹µP°ï 
									flag[3] = 1;
								}
								else											//µP°ï¥¼¹F¤W­­
								{
									table[3][flag[3]] = value[0];				//¥d¤ù©ñ¤J¦¹µP°ï 
									flag[3]++;
								}
							}
							else if(value[0] > table[2][flag[2]-1])				//·í¥d¤ù¤j¤p¤j©ótable[2]
							{
								if(flag[2] == 5)								//·íµP°ï¹F¨ì¤W­­ 
								{
									for( int32_t x = 0 ; x < flag[2] ; x++)		//­pºâ¦¹µP°ï¤ûÀY¼Æ¶q
										player[i].score += count( table[2][x] );
									memset( table[2] , 0 , 5);					//resetµP°ï 
									table[2][0] = value[0];						//±N¥d¤ù©ñ¤J¦¹µP°ï 
									flag[2] = 1;
								}
								else											//µP°ï¥¼¹F¤W­­
								{
									table[2][flag[2]] = value[0];				//¥d¤ù©ñ¤J¦¹µP°ï
									flag[2]++;
								}
							}
							else if(value[0] > table[1][flag[1]-1])				//·í¥d¤ù¤j¤p¤j©ótable[1]
							{
								if(flag[1] == 5)								//·íµP°ï¹F¨ì¤W­­
								{
									for( int32_t x = 0 ; x < flag[1] ; x++)		//­pºâ¦¹µP°ï¤ûÀY¼Æ¶q
										player[i].score += count( table[1][x]);
									memset( table[1] , 0 , 5);					//resetµP°ï
									table[1][0] = value[0];						//±N¥d¤ù©ñ¤J¦¹µP°ï
									flag[1] = 1;
								}
								else											//µP°ï¥¼¹F¤W­­
								{
									table[1][flag[1]] = value[0];				//¥d¤ù©ñ¤J¦¹µP°ï
									flag[1]++;
								}
							}
							else												//·í¥d¤ù¤j¤p¤j©ótable[0]
							{
								if(flag[0] == 5)								//·íµP°ï¹F¨ì¤W­­
								{
									for( int32_t x = 0 ; x < flag[0] ; x++)		//­pºâ¦¹µP°ï¤ûÀY¼Æ¶q
										player[i].score += count( table[0][x]);	
									memset( table[0] , 0 , 5);					//resetµP°ï
									table[0][0] = value[0];						//±N¥d¤ù©ñ¤J¦¹µP°ï
									flag[0] = 1;
								}
								else											//µP°ï¥¼¹F¤W­­
								{
									table[0][flag[0]] = value[0];				//¥d¤ù©ñ¤J¦¹µP°ï
									flag[0]++;
								}
							}
							
							//¤è«K¨t²Î§P§O·í«eµP°ï¤j¤p µP°ï¤j¤p¥Ñ¤p¨ì¤j0-3 0³Ì¤p3³Ì¤j
							for( int32_t x = 0 ; x < 3 ; x++)
			 				{
			 					int32_t banner , min = table[x][flag[x]-1];
			                	for( int32_t y = x+1 ; y < 4; y++)
			                	{
			                		if(min > table[y][flag[y]-1])
			                		{
			                			min = table[y][flag[y]-1];
										banner = y;
									}
			                	}
			                	for( int32_t z = 0 ; z < 5 ; z++)
			                	{
			                		int32_t reg = table[banner][z];
			                		table[banner][z] = table[x][z];
			                		table[x][z] = reg;
			                		
			                		reg = flag[banner];
			                		flag[banner] = flag[x];
			                		flag[x] = reg;
			                	}
							}
						}
					}
                }
                //end play
                if(player[i].score < player[j].score)			//player i win
                {
                	win[i][j]++;
                	fprintf(output,"%d:Win\t%d:Lose\n",i,j);
                }
                else	if(player[i].score > player[j].score)	//player j win
                		{
                			win[j][i]++;
                			fprintf(output,"%d:Lose\t%d:Win\n",i,j);
                		}
            			else
            			{
            				fprintf(output,"%d:Draw\t%d:Draw\n",i,j);
            			}
            }
            // i vs j 1000 run finish
        }
    }		//game finish
    //win
    for(int32_t i = 0; i<NUMBER; i++)
    {
    	for(int32_t j = 0; j<NUMBER; j++)
    		fprintf(output,"%d\t",win[i][j]);
    	fprintf(output,"\n");
    }
    //lose
    for(int32_t i = 0; i<NUMBER; i++)
    {
    	for(int32_t j = 0; j<NUMBER; j++)
    		fprintf(output,"%d\t",1000-win[i][j]);
    	fprintf(output,"\n");
    }
    return 0;
}

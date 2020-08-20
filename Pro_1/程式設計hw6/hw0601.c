#include <stdio.h>
#include <stdint.h>
#include "hw0601.h"	//引入助教標頭檔&&自己寫進的函式庫
//備註：將主要函式丟進hw0601_header.c，宣告在hw0601.h內

int main(){
	
	//宣告四位玩家的手牌陣列
	uint8_t player1[13] = {0};
	uint8_t player2[13] = {0};
	uint8_t player3[13] = {0};
	uint8_t player4[13] = {0};

	//使用助教的shuffle抽牌給玩家
	shuffle(player1, player2, player3, player4) ;

	//先印剛開始的牌長怎樣
	printf("Before:\n");
	print_card(player1);
	print_card(player2);
	print_card(player3);
	print_card(player4);

	//四個玩家的牌沒有問題(一張牌出現兩次、超出範圍==>出老千)
	//就開始根據三種型態印出來
	if (!(check_card(player1, player2, player3, player4))){

		//四個玩家手牌依序按照方法一排序，並印出來
		printf("Type 01:\n");
		sort_card(player1, func01);
		sort_card(player2, func01);
		sort_card(player3, func01);
		sort_card(player4, func01);
		print_card(player1);
		print_card(player2);
		print_card(player3);
		print_card(player4);

		//四個玩家手牌依序按照方法二排序，並印出來
		printf("Type 02:\n");
		sort_card(player1, func02);
		sort_card(player2, func02);
		sort_card(player3, func02);
		sort_card(player4, func02);
		print_card(player1);
		print_card(player2);
		print_card(player3);
		print_card(player4);

		//四個玩家手牌依序按照方法三排序，並印出來(個人解讀為「先排數字，再排花色。」)
		printf("Type 03:\n");
		sort_card(player1, func03);
		sort_card(player2, func03);
		sort_card(player3, func03);
		sort_card(player4, func03);
		print_card(player1);
		print_card(player2);
		print_card(player3);
		print_card(player4);

		//四個玩家手牌「先排花色，再排數字。」
		printf("Type 04:\n");
		sort_card(player1, func04);
		sort_card(player2, func04);
		sort_card(player3, func04);
		sort_card(player4, func04);
		print_card(player1);
		print_card(player2);
		print_card(player3);
		print_card(player4);
	}else{
		//有人出老千就提示Warning Messege
		printf("The following are possible conditions\n");
		printf("1) More than four cards with one point.\n");
		printf("2) Range isn't between [1,52]\n");
		printf("Warning Messege!(someone cheating)\n");	
	}

	return 0;
}

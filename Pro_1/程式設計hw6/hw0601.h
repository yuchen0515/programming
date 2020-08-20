#pragma once

void shuffle(uint8_t *player1, uint8_t *player2, uint8_t *player3, uint8_t *player4); 
void print_card(const uint8_t player[13]);
int32_t check_card(uint8_t a[13], uint8_t b[13], uint8_t c[13], uint8_t d[13]);
int32_t func01(int32_t a, int32_t b);
int32_t func02(int32_t a, int32_t b);
int32_t func03(int32_t a, int32_t b);
int32_t func04(int32_t a, int32_t b);
void sort_card(uint8_t player[13], int32_t (*compare)(int32_t a, int32_t b));

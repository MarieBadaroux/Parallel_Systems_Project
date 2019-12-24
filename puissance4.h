#define NB_COLUMN 7
#define NB_LINE 6
#define PLAYER1 1
#define PLAYER2 2

#include <stdint.h>

extern uint8_t grid[NB_LINE][NB_COLUMN];

void display_grid(void);
uint8_t play(uint8_t column, uint8_t player);
uint8_t win_horizontal(uint8_t line, uint8_t player);
uint8_t win_vertical(uint8_t column, uint8_t player);
uint8_t win_diagonal(uint8_t line, uint8_t column, uint8_t player);
uint8_t check_win(uint8_t line, uint8_t column, uint8_t player);
uint8_t is_full(uint8_t column);

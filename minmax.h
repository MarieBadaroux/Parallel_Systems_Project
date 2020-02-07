#include <stdbool.h>
#include <stdint.h>

#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#define DEPTH 2

uint8_t *possible_positions(void);
uint8_t check_play(uint8_t column, uint8_t player);
int stupid_evaluation(uint8_t column, uint8_t player, bool maximizingPlayer);
int horizontal_alignement(uint8_t line, uint8_t column, uint8_t player);
int vertical_alignement(uint8_t line, uint8_t column, uint8_t player);
int diagonal_alignement(uint8_t line, uint8_t column, uint8_t player);
int simple_evaluation(uint8_t column, uint8_t player, bool maximizingPlayer);
void play_for_minmax(uint8_t column, uint8_t player);
void undo_for_minmax(uint8_t column, uint8_t player);
int minimax(uint8_t column, uint8_t depth, bool maximizingPlayer, uint8_t player);
uint8_t play_minimax(uint8_t player);

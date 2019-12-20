#include <stdbool.h>

#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#define DEPTH 3

int *possible_positions(void);
int check_play(int column, int player);
int evaluation(int column, int player, bool maximizingPlayer);
int minimax(int column, int depth, bool maximizingPlayer, int player);
int play_minimax(int player);

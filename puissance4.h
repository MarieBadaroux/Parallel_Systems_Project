#define NB_COLUMN 7
#define NB_LINE 6
#define PLAYER1 1
#define PLAYER2 2

extern int grid[NB_LINE][NB_COLUMN];

void display_grid(void);
int play(int column, int player);
int win_horizontal(int line, int player);
int win_vertical(int column, int player);
int win_diagonal(int line, int column, int player);
int check_win(int line, int column, int player);
int is_full(int column);

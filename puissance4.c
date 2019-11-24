#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "puissance4.h"

#define NB_COLUMN 7
#define NB_LINE 6
#define PLAYER1 1
#define PLAYER2 2

static int grid[NB_LINE][NB_COLUMN] = {{0}};


void display_grid(void) {
	printf("\n");

	for (int i = 1; i < NB_COLUMN + 1; i++) {
		printf("  %i ", i);
	}
	printf("\n");

	for (int i = 0; i < NB_COLUMN + 1; i++) {
		if (i == 0) {
			printf("+");
			continue;
		}
		printf("---+");
	}
	printf("\n");

	for (int i = 0; i < NB_LINE; i++) {
		for (int j = 0; j < NB_COLUMN + 1; j++) {
			if (j == 0) {
				printf("|");
				continue;
			}
			if (grid[i][j-1] != 0) {
				printf(" %i |", grid[i][j-1]);
			} else {
				printf("   |");
			}
		}
		printf("\n");
		for (int k = 0; k < NB_COLUMN + 1; k++) {    
			if (k == 0) {
				printf("+");
				continue;
			}
			printf("---+");
		}
		printf("\n");
	}
}


int play(int column, int player) {
	int win;
	// If the column is full
	if (grid[0][column-1] != 0) {
		return 0;
	}

	for (int i = 1; i < NB_LINE; i++) {
		if (grid[i][column-1] != 0) {
			grid[i-1][column-1] = player;
			win = win_vertical(column-1, player);
			if (win == 1) {
				return 1;
			}
			return 0;
		}
		// If we play on the last line
		if (i == NB_LINE - 1) {
			grid[i][column-1] = player;
			win = win_vertical(column, player);
			if (win == 1) {
				return 1;
			}
			return 0;
		}
	}
	return 0;
}


int win_horizontal(int line, int player) {
	int win = 0;
	int count = 1;
	int symbol = player;
	int previous = grid[line][0];
	int current;

	// Check on the line if 4 symbols aligned
	for (int j = 1; j < NB_COLUMN; j++) {
		current = grid[line][j];
		if (current == symbol && current == previous) {
			count += 1;
		} else {
			count = 1;
		}

		// If 4 aligned
		if (count == 4) {
			win = 1;
			break;
		}
		previous = current;
	}
	return win;
}


int win_vertical(int column, int player) {
	int win = 0;
	int count = 1;
	int symbol = player;
	int previous = grid[0][column];
	int current;

	// Check on the column if 4 symbols aligned
	for (int i = 1; i < NB_LINE; i++) {
		current = grid[i][column];
		if (current == symbol && current == previous) {
			count += 1;
		} else {
			count = 1;
		}

		// If 4 aligned
		if (count == 4) {
			win = 1;
			break;
		}
		previous = current;
	}
	return win;
}


int main(void) {
	int player1_column;
	int player2_column;
	int win;
	
	display_grid();

	while(1) {
		printf("Player 1 : ");
		scanf("%d", &player1_column);
		while (player1_column < 1 || player1_column > 7) {
			printf("Player 1 : Error enter again the column = ");
			scanf("%d", &player1_column);
		}
		win = play(player1_column, PLAYER1);
		display_grid();
		if (win == 1) {
			printf("The player 1 win the game \n");
			break;
		}

		printf("Player 2 : ");
		scanf("%d", &player2_column);
		while (player2_column < 1 || player2_column > 7) {
			printf("Player 2 : Error enter again the column = ");
			scanf("%d", &player2_column);
		}
		win = play(player2_column, PLAYER2);
		display_grid();
		if (win == 1) {
			printf("The player 2 win the game \n");
			break;
		}
	}
	return EXIT_SUCCESS;
}

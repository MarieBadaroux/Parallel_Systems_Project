#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "puissance4.h"
#include "minmax.h"


uint8_t grid[NB_LINE][NB_COLUMN] = {{0}};


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
				printf(" %u |", grid[i][j-1]);
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


uint8_t is_full(uint8_t column) {
	if (grid[0][column] != 0) {
		return 1;
	}
	return 0;
}


uint8_t play(uint8_t column, uint8_t player) {
	for (int i = 1; i < NB_LINE; i++) {
		if (grid[i][column] != 0) {
			grid[i-1][column] = player;
			if (check_win(i-1, column, player) == 1) {
				return 1;
			}
			return 0;
		}
		// If we play on the last line
		if (i == NB_LINE - 1) {
			grid[i][column] = player;
			if (check_win(i, column, player) == 1) {
				return 1;
			}
			return 0;
		}
	}
	return 0;
}


uint8_t win_horizontal(uint8_t line, uint8_t player) {
	uint8_t win = 0;
	uint8_t count = 1;
	uint8_t symbol = player;
	uint8_t previous = grid[line][0];
	uint8_t current;

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


uint8_t win_vertical(uint8_t column, uint8_t player) {
	uint8_t win = 0;
	uint8_t count = 1;
	uint8_t symbol = player;
	uint8_t previous = grid[0][column];
	uint8_t current;

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


uint8_t win_diagonal(uint8_t line, uint8_t column, uint8_t player) {
	uint8_t win = 0;
	uint8_t count = 1;
	uint8_t symbol = player;
	uint8_t current;
	uint8_t previous;

	// Right diagonal
	uint8_t i = line;
	uint8_t j = column;
	// Find the lowest extremity of the diagonal
	while (i < NB_LINE && j > 0) {
		i++;
		j--;
	}

	previous = grid[i][j];
	// Go up in the diagonal
	while (i > 0 && j < NB_COLUMN) {
		i--;
		j++;
		current = grid[i][j];
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


	// Left diagonal
	i = line;
	j = column;
	// Find the lowest extremity of the diagonal
	while (i < NB_LINE && j < NB_COLUMN) {
		i++;
		j++;
	}

	previous = grid[i][j];
	// Go up in the diagonal
	while(i > 0 && j > 0) {
		i--;
		j--;
		current = grid[i][j];
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


uint8_t check_win(uint8_t line, uint8_t column, uint8_t player) {
	if (win_horizontal(line, player) || win_vertical(column, player) || win_diagonal(line, column, player)) {
		return 1;
	}
	return 0;
}


int main(void) {
	uint8_t player1_column;
#if 0
	uint8_t player2_column;
#endif
	uint8_t win;
	
	display_grid();

	while(1) {
		// If all columns are full
		if (is_full(0) && is_full(1) && is_full(2) && is_full(3) && is_full(4) && is_full(5) && is_full(6)) {
			printf("Nobody can play anymore \n"); 
		}

		// PLAYER 1
		printf("Player 1 : ");
		scanf("%hhu", &player1_column);
		
		// If the number of the colonne is not good
		while (player1_column < 1 || player1_column > 7) {
			printf("Player 1 : Error enter again the column = ");
			scanf("%hhu", &player1_column);
		}

		// If the column is full
		while (is_full(player1_column-1)) {
			printf("Player 1 : Error column full, enter an other column = ");
			scanf("%hhu", &player1_column);
		}

		// Now we can play
		win = play(player1_column-1, PLAYER1);
		display_grid();
		if (win == 1) {
			printf("Player 1 wins the game \n");
			break;
		}

		// PLAYER 2
		printf("Player 2 : ");
		win = play_minimax(PLAYER2);

#if 0
		scanf("%d", &player2_column);
		while (player2_column < 1 || player2_column > 7) {
			printf("Player 2 : Error enter again the column = ");
			scanf("%d", &player2_column);
		}
		win = play(player2_column, PLAYER2);
#endif

		display_grid();
		if (win == 1) {
			printf("Player 2 wins the game \n");
			break;
		}
	}
	return EXIT_SUCCESS;
}

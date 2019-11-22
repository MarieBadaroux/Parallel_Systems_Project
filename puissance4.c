#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "puissance4.h"

#define NB_COLUMN 7
#define NB_LINE 6
#define PLAYER1 1
#define PLAYER2 2

static char grid[NB_LINE][NB_COLUMN];


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
			if (isalpha(grid[i][j-1])) {
				printf(" %c |", grid[i][j-1]);
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


void play(int column, int player) {
	// If the column is full
	if (isalpha(grid[0][column-1])) {
		return;
	}

	for (int i = 0; i < NB_LINE; i++) {
		if (isalpha(grid[i][column-1])) {
			if (player == 1) {
				grid[i-1][column-1] = 'O';
			} else {
				grid[i-1][column-1] = 'X';
			}
			return;
		}
		// If we play on the last line
		if (i == NB_LINE - 1) {
			if (player == 1) {
				grid[i][column-1] = 'O';
			} else {
				grid[i][column-1] = 'X';
			}
			return;
		}
	}
}


int win_horizontal(int line, int column) {
	return 0;
}


int main(void) {
	int player1_column;
	int player2_column;

	while(1) {
		printf("Player 1 : ");
		scanf("%d", &player1_column);
		while (player1_column < 1 || player1_column > 7) {
			printf("Player 1 : Error enter again the column = ");
			scanf("%d", &player1_column);
		}
		play(player1_column, PLAYER1);
		display_grid();

		printf("Player 2 : ");
		scanf("%d", &player2_column);
		while (player2_column < 1 || player2_column > 7) {
			printf("Player 2 : Error enter again the column = ");
			scanf("%d", &player2_column);
		}
		play(player2_column, PLAYER2);
		display_grid();
	}
	return EXIT_SUCCESS;
}

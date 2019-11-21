#include <stdio.h>
#include <stdlib.h>
#include "puissance4.h"

#define NB_COLUMN 7
#define NB_LINE 6

//static struct position player1_positions[22];
//static struct position player2_positions[22];


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
			printf("   |");
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



int main(void) {
	display_grid();
	return EXIT_SUCCESS;
}

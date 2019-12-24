#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "puissance4.h"
#include "minmax.h"


uint8_t *possible_positions(void) {
	// the vector will contains 1 at the indice corresponding to the column if it is possible to play
	uint8_t *vector = calloc(7, sizeof(uint8_t));
	for (int j = 0; j < NB_COLUMN; j++) {
		// If the column is not full
		if (grid[0][j] == 0) {
			vector[j] = 1;
		}
	}
	return vector;
}


uint8_t check_play(uint8_t column, uint8_t player) {
	for (int i = 1; i < NB_LINE; i++) {
		if (grid[i][column] != 0) {
			if (check_win(i-1, column, player)) {
				return 1;
			}
			return 0;
		}

		// If we play on the last line
		if (i == NB_LINE - 1) {
			if (check_win(i, column, player)) {
				return 1;
			}
			return 0;
		}
	}
	return 0;
}


int stupid_evaluation(uint8_t column, uint8_t player, bool maximizingPlayer) {
	if (maximizingPlayer) {
		return check_play(column, player);
	}
	return -check_play(column, player);
}


int minimax(uint8_t column, uint8_t depth, bool maximizingPlayer, uint8_t player) {
	int eval;
	uint8_t *vect;
	if (depth == 0) {
		return stupid_evaluation(column, player, maximizingPlayer);
	}

	if (maximizingPlayer) {
		int maxEval = INT_MIN;
		vect = possible_positions();
		for (int j = 0; j < NB_COLUMN; j++) {
			if (vect[j] == 1) {
				eval = minimax(j, depth-1, false, player);
				maxEval = max(maxEval, eval);
			}
		}
		return maxEval;
	}

	else {
		int minEval = INT_MAX;
		vect = possible_positions();
		for (int k = 0; k < NB_COLUMN; k++) {
			if (vect[k] == 1) {
				eval = minimax(k, depth-1, true, player);
				minEval = min(minEval, eval);
			}
		}
		return minEval;
	}
}


uint8_t play_minimax(uint8_t player) {
	uint8_t *vec = possible_positions();
	for (int i = 0; i < NB_COLUMN; i++) {
		printf("%u ", vec[i]);
	}
	printf("\n");
	int res[NB_COLUMN] = {INT_MIN,INT_MIN,INT_MIN,INT_MIN,INT_MIN,INT_MIN,INT_MIN};
	int best_res = INT_MIN;
	uint8_t best_column;

	for (int i = 0; i < NB_COLUMN; i++) {
		if (vec[i] == 1) {
			res[i] = minimax(i, DEPTH, true, player);
		}
	}

	printf("\n res :");
	for (int i = 0; i < NB_COLUMN; i++) {
		printf("%i ", res[i]);
	}
	
	for (int j = 0; j < NB_COLUMN; j++) {
		if (res[j] != INT_MIN && res[j] >= best_res) {
			best_res = res[j];
			best_column = j;
		}
	}

	printf("\n best column : %u", best_column);

	// We can finaly play
	return play(best_column, player);
}

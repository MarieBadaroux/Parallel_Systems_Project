#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "puissance4.h"
#include "minmax.h"


int *possible_positions() {
	// the vector will contains 1 at the indice corresponding to the column if it is possible to play
	int *vector = calloc(7, sizeof(int));
	for (int j = 0; j < NB_COLUMN; j++) {
		// If the column is not full
		if (grid[0][j] == 0) {
			vector[j] = 1;
		}
	}
	return vector;
}


int check_play(int column, int player) {
	// If the column is full
	if (grid[0][column] != 0) {
		return 0;
	}

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


int evaluation(int column, int player, bool maximizingPlayer) {
	if (maximizingPlayer) {
		return check_play(column, player);
	}
	return -check_play(column, player);
}

int minimax(int column, int depth, bool maximizingPlayer, int player) {
	int eval;
	int *vect;
	if (depth == 0) {
		return evaluation(column, player, maximizingPlayer);
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


int play_minimax(int player) {
	int *vec = possible_positions();
	int res[NB_COLUMN];
	int best_res = INT_MIN;
	int best_column;

	for (int i = 0; i < NB_COLUMN; i++) {
		if (vec[i] == 1) {
			res[i] = minimax(i, DEPTH, true, player);
		}
	}
	
	for (int j = 0; j < NB_COLUMN; j++) {
		if (res[j] > best_res) {
			best_res = res[j];
			best_column = j;
		}
	}

	// We can finaly play
	return play(best_column+1, player);
}

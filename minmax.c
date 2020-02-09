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


int get_heuristic_cost_simple(uint8_t aligned) {
	switch (aligned) {
		case 1:
			return 1;
		case 2:
			return 5;
		case 3:
			return 50;
		case 4:
			return 1000;
		default:
			return 5000;
	};
}


int get_heuristic_cost(uint8_t aligned, uint8_t free) {
	if (aligned+free < 3)
		return 0;
	return get_heuristic_cost_simple(aligned);
}


int horizontal_alignement(uint8_t line, uint8_t column, uint8_t player) {
	uint8_t aligned = 1;
	uint8_t free = 0;
	int8_t j = column;
	uint8_t current;

	// Check aligned disk on the left
	while (j > 0) {
		j--;
		current = grid[line][j];
		if (current == player) {
			aligned++;
		} else {
			break;
		}
	}

	// Count the free places at the left extremity
	while (j >= 0) {
		current = grid[line][j];
		if (current == 0) {
			free++;
		} else {
			break;
		}
		j--;
	}

	// Check aligned disk on the right
	j = column;
	while (j < 6) {
		j++;
		current = grid[line][j];
		if (current == player) {
			aligned++;
		} else {
			break;
		}
	}

	// Count the free places at the right extremity
	while (j <= 6) {
		current = grid[line][j];
		if (current == 0) {
			free++;
		} else {
			break;
		}
		j++;
	}

	// Return the heuristic value
	return get_heuristic_cost_simple(aligned);
}


int vertical_alignement(uint8_t line, uint8_t column, uint8_t player) {
	uint8_t aligned = 1;
	uint8_t free = 0;
	int8_t i = line;
	uint8_t current;

	// Go down to count aligned disk
	while (i < 5) {
		i++;
		current = grid[i][column];
		if (current == player) {
			aligned++;
		} else {
			break;
		}
	}

	// Count the free places above
	i = line;
	while (i > 0) {
		i--;
		free++;
	}

	// Return the heuristic value
	return get_heuristic_cost_simple(aligned);
}


int diagonal_alignement(uint8_t line, uint8_t column, uint8_t player) {
	uint8_t aligned = 1;
	uint8_t free = 0;
	int8_t i = line;
	int8_t j = column;
	uint8_t current;

	int final_cost;

	// FIRST DIAGONAL
	// --------------

	// Count aligned disk up
	while (i > 0 && j > 0) {
		i--;
		j--;
		current = grid[i][j];
		if (current == player) {
			aligned++;
		} else {
			break;
		}
	}

	// Count free places up
	while (i >= 0 && j >= 0) {
		current = grid[i][j];
		if (current == 0) {
			free++;
		} else {
			break;
		}
		i--;
		j--;
	}

	// Count aligned disk down
	i = line;
	j = column;
	while (i < 5 && j < 6) {
		i++;
		j++;
		current = grid[i][j];
		if (current == player) {
			aligned++;
		} else {
			break;
		}
	}

	// Count free places down
	while (i <= 5 && j <= 6) {
		current = grid[i][j];
		if (current == 0) {
			free++;
		} else {
			break;
		}
		i++;
		j++;
	}

	// Calculate the heuristic value
	final_cost = get_heuristic_cost_simple(aligned);

	// SECOND DIAGONAL
	// ---------------

	aligned = 1;
	free = 0;
	i = line;
	j = column;

	// Count aligned disk up
	while (i > 0 && j < 6) {
		i--;
		j++;
		current = grid[i][j];
		if (current == player) {
			aligned++;
		} else {
			break;
		}
	}

	// Count free places up
	while (i >= 0 && j <= 6) {
		current = grid[i][j];
		if (current == 0) {
			free++;
		} else {
			break;
		}
		i--;
		j++;
	}

	// Count aligned disk down
	i = line;
	j = column;
	while (i < 5 && j > 0) {
		i++;
		j--;
		current = grid[i][j];
		if (current == player) {
			aligned++;
		} else {
			break;
		}
	}

	// Count free places down
	while (i <= 5 && j >= 0) {
		current = grid[i][j];
		if (current == 0) {
			free++;
		} else {
			break;
		}
		i++;
		j--;
	}

	// Calculate the heuristic value
	//final_cost += get_heuristic_cost_simple(aligned);
	final_cost = final_cost < get_heuristic_cost_simple(aligned)? get_heuristic_cost_simple(aligned):final_cost;
	return final_cost;
}


int simple_evaluation(uint8_t column, uint8_t player, bool maximizingPlayer) {
	// Find the line where the disk is
	uint8_t line;
	for (int i = 0; i < NB_LINE; i++) {
		if (grid[i][column] == player) {
			line = i;
			break;
		}
	}

	int cost = horizontal_alignement(line, column, player) + vertical_alignement(line, column, player) + diagonal_alignement(line, column, player);

	if (maximizingPlayer) {
		return cost;
	}
	return -cost;
}


void play_for_minmax(uint8_t column, uint8_t player) {
	for (int i = 1; i<NB_LINE; i++) {
		if (grid[i][column] != 0) {
			grid[i-1][column] = player;
			break;
		}

		// If we play on the last line
		if (i == NB_LINE - 1) {
			grid[i][column] = player;
			break;
		}
	}
}

void undo_for_minmax(uint8_t column, uint8_t player) {
	for (int i = 0; i < NB_LINE; i++) {
		if (grid[i][column] == player) {
			grid[i][column] = 0;
			break;
		}
	}
}


int minimax(uint8_t column, uint8_t depth, bool maximizingPlayer, uint8_t player) {
	int eval;
	uint8_t *vect;
	if (depth == 0) {
		return simple_evaluation(column, player, maximizingPlayer);
	}

	if (maximizingPlayer) {
		int maxEval = INT_MIN;
		vect = possible_positions();
		for (int j = 0; j < NB_COLUMN; j++) {
			if (vect[j] == 1) {
				play_for_minmax(j, player);
				eval = minimax(j, depth-1, false, PLAYER1);
				maxEval = max(maxEval, eval);
				undo_for_minmax(j, player);
			}
		}
		return maxEval;
	}

	else {
		int minEval = INT_MAX;
		vect = possible_positions();
		for (int k = 0; k < NB_COLUMN; k++) {
			if (vect[k] == 1) {
				play_for_minmax(k, player);
				eval = minimax(k, depth-1, true, PLAYER2);
				minEval = min(minEval, eval);
				undo_for_minmax(k, player);
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
			play_for_minmax(i, player);
			res[i] = minimax(i, DEPTH, true, player);
			undo_for_minmax(i, player);
		}
	}

	printf("\n res :");
	for (int i = 0; i < NB_COLUMN; i++) {
		printf("%i ", res[i]);
	}
	
	for (int j = 0; j < NB_COLUMN; j++) {
		if (res[j] != INT_MIN && res[j] > best_res) {
			best_res = res[j];
			best_column = j;
		}
	}

	// We can finaly play
	return play(best_column, player);
}

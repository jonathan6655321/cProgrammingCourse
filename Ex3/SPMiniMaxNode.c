#include "SPMiniMaxNode.h"

SPMiniMaxNode* spMiniMaxNodeCreate(SPFiarGame* game, int currentHeight) {
	if (!game) {
		return 0;
	}
	SPMiniMaxNode* minimaxnode = calloc(1, sizeof(SPMiniMaxNode));
	if (!minimaxnode) {
		printf(FUNCTION_ERROR, "calloc");
		abort();
	}
	minimaxnode->game = game;
	minimaxnode->currentHeight = currentHeight;

	minimaxnode->children = calloc(7, sizeof(SPFiarGame*));
	if (!(minimaxnode->children)) {
		printf(FUNCTION_ERROR, "calloc");
		abort();
	}
	if (currentHeight != 0 && spFiarCheckWinner(game) == 0) {
		for (int i = 0; i < 7; i++) {
			if (spFiarGameIsValidMove(game, i)) {
				SPFiarGame* spfiargame = spFiarGameCopy(game);

				spFiarGameSetMove(spfiargame, i);
				minimaxnode->children[i] = spMiniMaxNodeCreate(spfiargame,
						currentHeight - 1);
				if (!minimaxnode->children[i]) {
					spFiarGameDestroy(spfiargame);
				}
			}
		}
	}
	return minimaxnode;

}

void spMiniMaxNodeDestroy(SPMiniMaxNode* node) {
	for (int i = 0; i < 7; i++) {
		if (node->children[i]) {
			spMiniMaxNodeDestroy(node->children[i]);
		}
	}
	free(node->children);
	spFiarGameDestroy(node->game);
	free(node);
}

int countHorizontalScore(SPFiarGame* game, int *spanScores) {
	int i, j, k, currentSpanScore;
	char currentChar;
	for (i = 0; i < SP_FIAR_GAME_N_ROWS; i++) {
		for (j = 0; j < SP_FIAR_GAME_N_COLUMNS - 3; j++) {
			currentSpanScore = 0;
			for (k = 0; k < 4; k++) {
				currentChar = (game->gameBoard)[i][j + k];
				if (SP_FIAR_GAME_PLAYER_1_SYMBOL == currentChar) {
					currentSpanScore++;
				} else if (SP_FIAR_GAME_PLAYER_2_SYMBOL == currentChar) {
					currentSpanScore--;
				}
			}
			if (currentSpanScore == 4) {
				return INT_MAX;
			} else if (currentSpanScore == -4) {
				return INT_MIN;
			} else {
				if (currentSpanScore < 0) {
					spanScores[currentSpanScore + 3]++;
				} else if (currentSpanScore > 0) {
					spanScores[currentSpanScore + 2]++;
				}
			}
		}
	}
	return 0;
}

int countVerticalScore(SPFiarGame* game, int *spanScores) {
	// count vertical 4's:
	int i, j, k, currentSpanScore;
	char currentChar;
	for (j = 0; j < SP_FIAR_GAME_N_COLUMNS; j++) {
		for (i = 0; i < SP_FIAR_GAME_N_ROWS - 3; i++) {
			currentSpanScore = 0;
			for (k = 0; k < 4; k++) {
				currentChar = (game->gameBoard)[i + k][j];
				if (SP_FIAR_GAME_PLAYER_1_SYMBOL == currentChar) {
					currentSpanScore++;
				} else if (SP_FIAR_GAME_PLAYER_2_SYMBOL == currentChar) {
					currentSpanScore--;
				}
			}
			if (currentSpanScore == 4) {
				return INT_MAX;
			} else if (currentSpanScore == -4) {
				return INT_MIN;
			} else {
				if (currentSpanScore < 0) {
					spanScores[currentSpanScore + 3]++;
				} else if (currentSpanScore > 0) {
					spanScores[currentSpanScore + 2]++;
				}
			}
		}
	}
	return 0;
}

int countDiagonalScoreLeftToRight(SPFiarGame* game, int *spanScores) {
	// count diagonals 4's (top left to bottom right)
	int i, j, k, currentSpanScore;
	char currentChar;
	for (i = 0; i < SP_FIAR_GAME_N_ROWS - 3; i++) {
		for (j = 0; j < SP_FIAR_GAME_N_COLUMNS - 3; j++) {
			currentSpanScore = 0;
			for (k = 0; k < 4; k++) {
				currentChar = (game->gameBoard)[i + k][j + k];
				if (SP_FIAR_GAME_PLAYER_1_SYMBOL == currentChar) {
					currentSpanScore++;
				} else if (SP_FIAR_GAME_PLAYER_2_SYMBOL == currentChar) {
					currentSpanScore--;
				}
			}
			if (currentSpanScore == 4) {
				return INT_MAX;
			} else if (currentSpanScore == -4) {
				return INT_MIN;
			} else {
				if (currentSpanScore < 0) {
					spanScores[currentSpanScore + 3]++;
				} else if (currentSpanScore > 0) {
					spanScores[currentSpanScore + 2]++;
				}
			}
		}
	}
	return 0;
}

int countDiagonalScoreRightToLeft(SPFiarGame* game, int *spanScores) {
	// count diagonals 4's (top right to bottom left)
	int i, j, k, currentSpanScore;
	char currentChar;
	for (i = 0; i < SP_FIAR_GAME_N_ROWS - 3; i++) {
		for (j = 3; j < SP_FIAR_GAME_N_COLUMNS; j++) {
			currentSpanScore = 0;
			for (k = 0; k < 4; k++) {
				currentChar = (game->gameBoard)[i + k][j - k];
				if (SP_FIAR_GAME_PLAYER_1_SYMBOL == currentChar) {
					currentSpanScore++;
				} else if (SP_FIAR_GAME_PLAYER_2_SYMBOL == currentChar) {
					currentSpanScore--;
				}
			}
			if (currentSpanScore == 4) {
				return INT_MAX;
			} else if (currentSpanScore == -4) {
				return INT_MIN;
			} else {
				if (currentSpanScore < 0) {
					spanScores[currentSpanScore + 3]++;
				} else if (currentSpanScore > 0) {
					spanScores[currentSpanScore + 2]++;
				}
			}
		}
	}
	return 0;
}

int calculateGameUtilityValue(SPFiarGame* game) {
	int spanScores[6] = { 0, 0, 0, 0, 0, 0 }; // -3,-2,-1,1,2,3
	const int weights[6] = { -5, -2, -1, 1, 2, 5 };

	int hor = countHorizontalScore(game, spanScores);
	if (hor != 0) {
		return hor;
	}

	int ver = countVerticalScore(game, spanScores);
	if (ver != 0) {
		return ver;
	}

	int diagLtR = countDiagonalScoreLeftToRight(game, spanScores);
	if (diagLtR != 0) {
		return diagLtR;
	}

	int diagRtL = countDiagonalScoreRightToLeft(game, spanScores);
	if (diagRtL != 0) {
		return diagRtL;
	}

	int totalScore = 0;
	for (int i = 0; i < 6; i++) {
		totalScore += weights[i] * spanScores[i];
	}
	return totalScore;
}

int getNodeUtilityValue(SPMiniMaxNode* node) {
	if (node->currentHeight == 0) {
		node->utilityValue = calculateGameUtilityValue(node->game);
	} else {
		int min = INT_MAX;
		int max = INT_MIN;
		int hasChildren = 0;
		int currentValue = 0;
		for (int i = 0; i < 7; i++) {
			if (node->children[i]) {
				hasChildren = 1;
				currentValue = getNodeUtilityValue(node->children[i]);
				min = (min > currentValue) ? currentValue : min;
				max = (max < currentValue) ? currentValue : max;
			}
		}
		if (!hasChildren) {
			node->utilityValue = calculateGameUtilityValue(node->game);
		} else {
			if (node->game->currentPlayer == 0) {
				node->utilityValue = max;
			} else {
				node->utilityValue = min;
			}
		}
	}
	return node->utilityValue;
}

int getOptimalMoveFromNode(SPMiniMaxNode* node) {
	int optimalValue = getNodeUtilityValue(node);
	for (int i = 0; i < 7; i++) {
		if (node->children[i] != 0
				&& node->children[i]->utilityValue == optimalValue) {
			return i;
		}
	}
	return -1;
}

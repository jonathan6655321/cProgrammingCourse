#include "SPFIARGame.h"

#define UNDO_MOVE_COMPUTER_STRING "Remove disc: remove computer’s disc at column %d\n"
#define UNDO_MOVE_PLAYER_STRING "Remove disc: remove user’s disc at column %d\n”"


SPFiarGame* spFiarGameCreate(int historySize) {
	if (historySize < 0) {
		return 0;
	}
	SPFiarGame* spfiargame = calloc(1, sizeof(SPFiarGame));
	if (!spfiargame) {
		printf(FUNCTION_ERROR, "calloc");
		abort();
	}
	memset(spfiargame->gameBoard, SP_FIAR_GAME_EMPTY_ENTRY,
			sizeof(spfiargame->gameBoard)); //set everything to " "
	spfiargame->historySize = historySize;
	spfiargame->history_turns_array = spArrayListCreate(historySize); // 1 turn per player TODO
	return spfiargame;

}

void spFiarGameDestroy(SPFiarGame* src) {
	spArrayListDestroy(src->history_turns_array);
	free(src);
}

SPFiarGame* spFiarGameCopy(SPFiarGame* src) {
	SPFiarGame* dest = spFiarGameCreate(src->historySize);
	memcpy(dest->gameBoard, src->gameBoard,
			SP_FIAR_GAME_N_ROWS * SP_FIAR_GAME_N_COLUMNS * sizeof(char));
	memcpy(dest->tops, src->tops, SP_FIAR_GAME_N_COLUMNS * sizeof(int));
	dest->history_turns_array = spArrayListCopy(src->history_turns_array);
	dest->currentPlayer = src->currentPlayer;
	return dest;
}

SP_FIAR_GAME_MESSAGE spFiarGameSetMove(SPFiarGame* src, int col) {
	if ((!src) || (col < 0) || (col > SP_FIAR_GAME_N_COLUMNS - 1)) {
		return SP_FIAR_GAME_INVALID_ARGUMENT;
	} else if (!spFiarGameIsValidMove(src, col)) {
		return SP_FIAR_GAME_INVALID_MOVE;
	}
	src->gameBoard[src->tops[col]][col] =
			SP_FIAR_GAME_PLAYERS_SYMBOL((int) src->currentPlayer);
	spArrayListPush(src->history_turns_array, col);
	src->tops[col]++;
	src->currentPlayer = !src->currentPlayer;
	return SP_FIAR_GAME_SUCCESS;
}

bool spFiarGameIsValidMove(SPFiarGame* src, int col) {
	return src->tops[col] != SP_FIAR_GAME_N_ROWS; //TODO < ??
}

SP_FIAR_GAME_MESSAGE spFiarGameUndoPrevMove(SPFiarGame* src) {
	if (!src) {
		return SP_FIAR_GAME_INVALID_ARGUMENT;
	} else if (spArrayListIsEmpty(src->history_turns_array)) {
		return SP_FIAR_GAME_NO_HISTORY;
	}
	int col = spArrayListPop(src->history_turns_array);
	if (src->currentPlayer) {
		printf(UNDO_MOVE_COMPUTER_STRING, col);
	} else {
		printf(UNDO_MOVE_PLAYER_STRING, col);
	}
	src->tops[col]--;
	src->gameBoard[src->tops[col]][col] = SP_FIAR_GAME_EMPTY_ENTRY;
	src->currentPlayer = !src->currentPlayer;
	return SP_FIAR_GAME_SUCCESS;
}

char spFiarGameGetCurrentPlayer(SPFiarGame* src) {
	if (!src) {
		return SP_FIAR_GAME_EMPTY_ENTRY;
	}
	return SP_FIAR_GAME_PLAYERS_SYMBOL((int) src->currentPlayer);
}

char spFiarCheckWinnerHorizontal(SPFiarGame* src) {
	char lastChar;
	int i, j, count;
	for (i = 0; i < SP_FIAR_GAME_N_ROWS; i++) {
		lastChar = 0;
		for (j = 0; j < SP_FIAR_GAME_N_COLUMNS; j++) {
			if (src->gameBoard[i][j] == lastChar) {
				count++;
			} else {
				count = 1;
				lastChar = src->gameBoard[i][j];
			}
			if (count == 4 && lastChar != SP_FIAR_GAME_EMPTY_ENTRY) {
				return lastChar;
			}
		}
	}
	return 0;
}

char spFiarCheckWinnerVerticaly(SPFiarGame* src) {
	char lastChar;
	int i, j, count;
	for (j = 0; j < SP_FIAR_GAME_N_COLUMNS; j++) {
		lastChar = 0;
		for (i = 0; i < SP_FIAR_GAME_N_ROWS; i++) {
			if (src->gameBoard[i][j] == lastChar) {
				count++;
			} else {
				count = 1;
				lastChar = src->gameBoard[i][j];
			}
			if (count == 4 && lastChar != SP_FIAR_GAME_EMPTY_ENTRY) {
				return lastChar;
			}
		}
	}
	return 0;
}

char spFiarCheckWinnerDaiagonalRight(SPFiarGame* src) {
	char lastChar;
	int i, j, count;
	int starti = SP_FIAR_GAME_N_ROWS - 1;
	int startj = 0;
	while (startj < SP_FIAR_GAME_N_COLUMNS) {
		i = starti;
		j = startj;
		lastChar = 0;
		while (i < SP_FIAR_GAME_N_ROWS && j < SP_FIAR_GAME_N_COLUMNS) {
			if (src->gameBoard[i][j] == lastChar) {
				count++;
			} else {
				count = 1;
				lastChar = src->gameBoard[i][j];
			}
			if (count == 4 && lastChar != SP_FIAR_GAME_EMPTY_ENTRY) {
				return lastChar;
			}
			i++;
			j++;
		}
		starti--;
		if (starti < 0) {
			starti = 0;
			startj++;
		}
	}
	return 0;
}

char spFiarCheckWinnerDaiagonalLeft(SPFiarGame* src) {
	char lastChar;
	int i, j, count;
	int starti = 0;
	int startj = 0;
	while (starti < SP_FIAR_GAME_N_ROWS) {
		i = starti;
		j = startj;
		lastChar = 0;
		while (i < SP_FIAR_GAME_N_ROWS && j >= 0) {
			if (src->gameBoard[i][j] == lastChar) {
				count++;
			} else {
				count = 1;
				lastChar = src->gameBoard[i][j];
			}
			if (count == 4 && lastChar != SP_FIAR_GAME_EMPTY_ENTRY) {
				return lastChar;
			}
			i++;
			j--;
		}
		startj++;
		if (startj == SP_FIAR_GAME_N_COLUMNS) {
			startj = SP_FIAR_GAME_N_COLUMNS - 1;
			starti++;
		}
	}
	return 0;
}

bool spFiarGameBoardIsFull(SPFiarGame* src) {
	for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
		if (src->tops[i] < SP_FIAR_GAME_N_ROWS) {
			return 0;
		}
	}
	return 1;
}

char spFiarCheckWinner(SPFiarGame* src) {
	if (!src) {
		return 0;
	}
	char res;
	res = spFiarCheckWinnerHorizontal(src);
	if (res != 0) {
		return res;
	}
	res = spFiarCheckWinnerVerticaly(src);
	if (res != 0) {
		return res;
	}
	res = spFiarCheckWinnerDaiagonalRight(src);
	if (res != 0) {
		return res;
	}
	res = spFiarCheckWinnerDaiagonalLeft(src);
	if (res != 0) {
		return res;
	}
	if (spFiarGameBoardIsFull(src)) {
		return SP_FIAR_GAME_TIE_SYMBOL;
	} else {
		return 0;
	}
}

SP_FIAR_GAME_MESSAGE spFiarGamePrintBoard(SPFiarGame* src) {
	if (!src) {
		return SP_FIAR_GAME_INVALID_ARGUMENT;
	}
	for (int i = SP_FIAR_GAME_N_ROWS - 1; i >= 0; i--) {
		printf("| ");
		for (int j = 0; j < SP_FIAR_GAME_N_COLUMNS; j++) {
			printf("%c ", src->gameBoard[i][j]);
		}
		printf("|\n");
	}
	for (int j = 0; j < 3 + SP_FIAR_GAME_N_COLUMNS * 2; j++) {
		printf("-");
	}
	printf("\n  ");
	for (int j = 1; j < SP_FIAR_GAME_N_COLUMNS + 1; j++) {
		printf("%d ", j);
	}
	printf(" \n");
	return SP_FIAR_GAME_SUCCESS;
}

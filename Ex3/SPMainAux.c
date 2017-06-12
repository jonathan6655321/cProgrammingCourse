#include "SPMainAux.h"

void initializeGame(SPFiarGame** spfiargame, int* maxDepth) {
	if (!(!(*spfiargame))) {
		spFiarGameDestroy((*spfiargame));
	}
	printf(DIFFICULTY_LEVEL_STRING);
	char str[1024];
	fgets(str, sizeof(str), stdin);
	if (strcmp(str, "quit") == 0) {
		printf(EXITING_STRING);
		abort();
	}
	while (!spParserIsInt(str)) {
		printf(INVALID_DIFFICULTY_LEVEL_ERROR_STRING);
		printf(DIFFICULTY_LEVEL_STRING);
		fgets(str, sizeof(str), stdin);
		if (strcmp(str, "quit") == 0) {
			printf(EXITING_STRING);
			abort();
		}
	}
	(*maxDepth) = spPaserPraseInt(str);

	(*spfiargame) = spFiarGameCreate(HISTORY_SIZE);
}

SPCommand getNextCommand() {
	char str[1024];
	fgets(str, sizeof(str), stdin);
	return spParserPraseLine(str);
}

int addDisk(SPCommand spCommand, SPFiarGame* spfiargame, int* gameIsRunning,
		int maxDepth) {
	SP_FIAR_GAME_MESSAGE retMessage = spFiarGameSetMove(spfiargame,
			spCommand.arg - 1);

	if (retMessage == SP_FIAR_GAME_INVALID_ARGUMENT) {
		printf(INVALID_COMMAND_STRING);
		return 0;
	} else if (retMessage == SP_FIAR_GAME_INVALID_MOVE) {
		printf(INVALID_COLOMN_NUMBER);
		return 0;
	}
	checkWinner(spfiargame, gameIsRunning);
	if (*gameIsRunning && 0) {
		addEnemyMove(spfiargame, maxDepth);
		checkWinner(spfiargame, gameIsRunning);
	}
	return 1;
}

void checkWinner(SPFiarGame* spfiargame, int* gameIsRunning) {
	char res = spFiarCheckWinner(spfiargame);
	if (res == SP_FIAR_GAME_PLAYER_1_SYMBOL) {
		spFiarGamePrintBoard(spfiargame);
		(*gameIsRunning) = 0;
		printf(GAME_OVER_PLAYER_1_WIN_STRING);
	} else if (res == SP_FIAR_GAME_PLAYER_2_SYMBOL) {
		spFiarGamePrintBoard(spfiargame);
		(*gameIsRunning) = 0;
		printf(GAME_OVER_PLAYER_2_WIN_STRING);
	} else if (res == SP_FIAR_GAME_TIE_SYMBOL) {
		spFiarGamePrintBoard(spfiargame);
		(*gameIsRunning) = 0;
		printf(GAME_OVER_TIE_STRING);
	}
}

void addEnemyMove(SPFiarGame* spfiargame, int maxDepth) {
	int optimalMove = spMinimaxSuggestMove(spfiargame, maxDepth);
	printf(COMPUTER_MOVE_STRING, optimalMove);
	spFiarGameSetMove(spfiargame, optimalMove);
}

int undoMove(SPFiarGame* spfiargame) {
	SP_FIAR_GAME_MESSAGE retMessage = spFiarGameUndoPrevMove(spfiargame);
	if (retMessage == SP_FIAR_GAME_NO_HISTORY) {
		printf(NO_HISTORY_ERROR_STRING);
		return 0;
	}
	return 1;
}

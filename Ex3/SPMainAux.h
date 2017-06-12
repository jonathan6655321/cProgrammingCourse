#ifndef SPMAINAUX_H_
#define SPMAINAUX_H_

#include <stdio.h>
#include "SPFIARGame.h"

#define HISTORY_SIZE 20
#define DIFFICULTY_LEVEL_STRING "Please enter the difficulty level between [1-7]:\n"
#define INVALID_DIFFICULTY_LEVEL_ERROR_STRING "Error: invalid level (should be between 1 to 7)\n"
#define INVALID_COMMAND_STRING "Error: invalid command\n"
#define INVALID_COLOMN_NUMBER "Error: column number must be in range 1-7\n"
#define GAME_OVER_PLAYER_1_WIN_STRING "Game over: you win\nPlease enter �quit� to exit or �restart� to start a new game!\n"
#define GAME_OVER_PLAYER_2_WIN_STRING "Game over: computer wins\nPlease enter �quit� to exit or �restart� to start a new game!\n"
#define GAME_OVER_TIE_STRING "Game over: it�s a tie\nPlease enter �quit� to exit or �restart� to start a new game!\n"
#define SUGGEST_MOVE_STRING "Suggested move: drop a disc to column %d\n"
#define COMPUTER_MOVE_STRING "Computer move: add disc to column%d\n"
#define EXITING_STRING "Exiting�\n"
#define RESTARTING_STRING "Game restarted!\n"
#define NO_HISTORY_ERROR_STRING "Error: cannot undo previous move!\n"
#define NOT_ALLOWED_COMMANDS "Error: the game is over\n"

void initializeGame(SPFiarGame** spfiargame, int* maxDepth) {
	if (!(!(*spfiargame))) {
		spFiarGameDestroy((*spfiargame));
	}
	int i;
	printf(DIFFICULTY_LEVEL_STRING);
	char str[1024];
	i = scanf("%s", str);
	if (strcmp(str, "quit")) {
		abort();
	}
	while (i == 0 || (!spParserIsInt(str))) {
		printf(INVALID_DIFFICULTY_LEVEL_ERROR_STRING);
		printf(DIFFICULTY_LEVEL_STRING);
		i = scanf("%s", str);
		if (strcmp(str, "quit")) {
			abort();
		}
	}
	(*maxDepth) = spPaserPraseInt(str);

	(*spfiargame) = spFiarGameCreate(HISTORY_SIZE);
}

SPCommand getNextCommand() {
	char str[1024];
	scanf("%[^\n]", str);
	return spParserPraseLine(str);
}

void addDisk(SPCommand spCommand, SPFiarGame* spfiargame, int* gameIsRunning,
		int maxDepth) {
	SP_FIAR_GAME_MESSAGE retMessage = spFiarGameSetMove(spfiargame,
			spCommand.arg);

	if (retMessage == SP_FIAR_GAME_INVALID_ARGUMENT) {
		printf(INVALID_COMMAND_STRING);
	} else if (retMessage == SP_FIAR_GAME_INVALID_MOVE) {
		printf(INVALID_COLOMN_NUMBER);
	}
	checkWinner(spfiargame, gameIsRunning);
	if (*gameIsRunning) {
		addEnemyMove(spfiargame, gameIsRunning);
		checkWinner(spfiargame, gameIsRunning);
	}
}

void checkWinner(SPFiarGame* spfiargame, int* gameIsRunning) {
	char res = spFiarCheckWinner(spfiargame);
	if (res == SP_FIAR_GAME_PLAYER_1_SYMBOL) {
		(*gameIsRunning) = 0;
		printf(GAME_OVER_PLAYER_1_WIN_STRING);
	} else if (res == SP_FIAR_GAME_PLAYER_2_SYMBOL) {
		(*gameIsRunning) = 0;
		printf(GAME_OVER_PLAYER_2_WIN_STRING);
	} else if (res == SP_FIAR_GAME_TIE_SYMBOL) {
		(*gameIsRunning) = 0;
		printf(GAME_OVER_TIE_STRING);
	}
}

void addEnemyMove(SPFiarGame* spfiargame, int* gameIsRunning, int maxDepth) {
	int optimalMove = spMinimaxSuggestMove(spfiargame, maxDepth);
	printf(COMPUTER_MOVE_STRING, optimalMove);
	spFiarGameSetMove(spfiargame, optimalMove);
}

void undoMove(SPFiarGame* spfiargame) {
	SP_FIAR_GAME_MESSAGE retMessage = spFiarGameUndoPrevMove(spfiargame);
	if (retMessage == SP_FIAR_GAME_NO_HISTORY) {
		printf(NO_HISTORY_ERROR_STRING);
	}
}

#endif

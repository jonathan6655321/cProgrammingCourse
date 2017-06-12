#include "SPMainAux.h"

int main() {
	SPFiarGame* spfiargame;
	int maxDepth;

	initializeGame(&spfiargame, &maxDepth);
	int gameIsRunning = 1;
	int needToPrint = 1;
	SPCommand spCommand;
	//gameLoop
	while (1) {
		if (gameIsRunning && needToPrint) {
			spFiarGamePrintBoard(spfiargame);
			printf(NEXT_MOVE_STRING);
			needToPrint = 0;
		}
		spCommand = getNextCommand();
		if (spCommand.validArg) {
			switch (spCommand.cmd) {
			case SP_ADD_DISC:
				if (gameIsRunning) {
					needToPrint = addDisk(spCommand, spfiargame, &gameIsRunning, maxDepth);
				} else {
					printf(NOT_ALLOWED_COMMANDS);
				}
				continue;

			case SP_SUGGEST_MOVE:
				if (gameIsRunning) {
					int optimalMove = spMinimaxSuggestMove(spfiargame,
							maxDepth);
					printf(SUGGEST_MOVE_STRING, optimalMove);
				} else {
					printf(NOT_ALLOWED_COMMANDS);
				}
				continue;

			case SP_UNDO_MOVE:
				needToPrint = undoMove(spfiargame);
				gameIsRunning = 1;
				continue;

			case SP_RESTART:
				printf(RESTARTING_STRING);
				initializeGame(&spfiargame, &maxDepth);
				needToPrint = 1;
				gameIsRunning = 1;
				continue;

			case SP_QUIT:
				break;
			case SP_INVALID_LINE:
				printf(INVALID_COMMAND_STRING);
				continue;
			}
		}
		printf(INVALID_COMMAND_STRING);
	}
	printf(EXITING_STRING);
	spFiarGameDestroy(spfiargame);
	return 0;
}


#include "SPMainAux.h"

int main() {
	SPFiarGame* spfiargame;
	int maxDepth;

	initializeGame(&spfiargame, &maxDepth);
	int gameIsRunning = 1;
	SPCommand spCommand;
	//gameLoop
	while (1) {
		spFiarGamePrintBoard(spfiargame);
		spCommand = getNextCommand();
		if (spCommand.validArg) {
			if (gameIsRunning && spCommand.cmd == SP_ADD_DISC) {
				addDisk(spCommand, &spfiargame, &maxDepth);
				continue;
			}
			if (gameIsRunning && spCommand.cmd == SP_UNDO_MOVE) {
			}
			if (gameIsRunning && spCommand.cmd == SP_SUGGEST_MOVE) {
			}
			if (spCommand.cmd == SP_QUIT) {
				break;
			}
			if (spCommand.cmd == SP_RESTART) {
				initializeGame(&spfiargame, &maxDepth);
				gameIsRunning = 1;
				continue;
			}
		}
		printf(INVALID_COMMAND_STRING);
	}

	spArrayListDestroy(spfiargame);
	return 0;
}


#include "SPMainAux.h"

int main() {
	SPFiarGame* spfiargame = 0;
	unsigned int maxDepth = 0;

	initializeGame(&spfiargame, &maxDepth);
	int gameIsRunning = 1;
	int needToPrint = 1;
	SPCommand spCommand;

	//gameLoop
	spCommand.cmd = SP_INVALID_LINE;
	while (spCommand.cmd != SP_QUIT) {
		if (gameIsRunning && needToPrint) {
			spFiarGamePrintBoard(spfiargame);
			printf(NEXT_MOVE_STRING);
			needToPrint = 0;
		}
		spCommand = getNextCommand();
		if (spCommand.cmd != SP_INVALID_LINE && spCommand.validArg) {
			handleCommand(spCommand, &spfiargame, &gameIsRunning, &needToPrint,
					&maxDepth);
		} else {
			if (spCommand.cmd == SP_ADD_DISC) {
				printf(INVALID_COLOMN_NUMBER);
			} else {
				printf(INVALID_COMMAND_STRING);
			}
		}
	}
	printf(EXITING_STRING);
	spFiarGameDestroy(spfiargame);
	return 0;
}


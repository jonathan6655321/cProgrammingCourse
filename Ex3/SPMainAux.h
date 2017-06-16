#ifndef SPMAINAUX_H_
#define SPMAINAUX_H_

#include <stdio.h>
#include "SPFIARGame.h"
#include "SPFIARParser.h"
#include "SPMiniMax.h"

#define HISTORY_SIZE 20
#define DIFFICULTY_LEVEL_STRING "Please enter the difficulty level between [1-7]:\n"
#define INVALID_DIFFICULTY_LEVEL_ERROR_STRING "Error: invalid level (should be between 1 to 7)\n"
#define INVALID_COMMAND_STRING "Error: invalid command\n"
#define INVALID_COLOMN_NUMBER "Error: column number must be in range 1-7\n"
#define GAME_OVER_PLAYER_1_WIN_STRING "Game over: you win\nPlease enter 'quit' to exit or 'restart' to start a new game!\n"
#define GAME_OVER_PLAYER_2_WIN_STRING "Game over: computer wins\nPlease enter 'quit' to exit or 'restart' to start a new game!\n"
#define GAME_OVER_TIE_STRING "Game over: it's a tie\nPlease enter 'quit' to exit or 'restart' to start a new game!\n"
#define SUGGEST_MOVE_STRING "Suggested move: drop a disc to column %d\n"
#define COMPUTER_MOVE_STRING "Computer move: add disc to column %d\n"
#define EXITING_STRING "Exiting...\n"
#define RESTARTING_STRING "Game restarted!\n"
#define NO_HISTORY_ERROR_STRING "Error: cannot undo previous move!\n"
#define NOT_ALLOWED_COMMANDS "Error: the game is over\n"
#define NEXT_MOVE_STRING "Please make the next move:\n"
#define COLUMN_FULL_ERROR_STRING "Error: column %d is full\n"

/* a initializing function that ask the user to input maxDepth,
 * and destroy last FIARGame and create a new one.
 */
void initializeGame(SPFiarGame** spfiargame, unsigned int* maxDepth);

/* ask the user to input next command.
 *
 * return: the command after parsing.
 */
SPCommand getNextCommand();

/*
 * add user move to game board and then if no winner add enemy move.
 *
 * return: 0 if there's a winner, and 1 if not.
 */
int addDisk(SPCommand spCommand, SPFiarGame* spfiargame, int* gameIsRunning,
		int maxDepth);

/*
 *check if there's a winner, and if so print the board and winning message and stop the game.
 */
void checkWinner(SPFiarGame* spfiargame, int* gameIsRunning);

/*
 * compute and add computer move to the game board.
 */
void addEnemyMove(SPFiarGame* spfiargame, int maxDepth);

/*
 * handle undo move command. undo 2 actions from the history (one user action and one of the computer action).
 *
 * return: 1 if successfully undo move, and 0 if not.
 */
int undoMove(SPFiarGame* spfiargame);

/* get SPCommand and handle it with the needed action.
 *
 * change gameIsRunning, needToPrint, maxDepth as needed.
 */
void handleCommand(SPCommand spCommand, SPFiarGame** spfiargame,
		int* gameIsRunning, int* needToPrint, unsigned int* maxDepth);
#endif

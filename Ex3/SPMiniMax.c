/*
 * SPMiniMax.c
 *
 *  Created on: 12 ???? 2017
 *      Author: kessi
 */
#include "SPMiniMax.h"

int spMinimaxSuggestMove(SPFiarGame* currentGame, unsigned int maxDepth) {
	if (!currentGame) {
		return -1;
	}
	SPFiarGame* currentGameClone = spFiarGameCopy(currentGame);
	SPMiniMaxNode* spMiniMaxNode = spMiniMaxNodeCreate(currentGameClone,
			maxDepth);
	int optimalMove = getOptimalMoveFromNode(spMiniMaxNode);
	spMiniMaxNodeDestroy(spMiniMaxNode);
	return optimalMove;
	return maxDepth;
}


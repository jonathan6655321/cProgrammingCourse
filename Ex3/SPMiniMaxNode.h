#include "SPFIARGame.h"
#include "limits.h"

#ifndef SPMINIMAXNODE_H_
#define SPMINIMAXNODE_H_

typedef struct MiniMaxNode {
	SPFiarGame* game;
	int currentHeight;
	int utilityValue;
	SPMiniMaxNode* children[7];
} SPMiniMaxNode;

SPMiniMaxNode* spMiniMaxNodeCreate(SPFiarGame* game, int currentHeight);

void spMiniMaxNodeDestroy(SPMiniMaxNode* node);

int calculateGameUtilityValue(SPFiarGame* game);

int getNodeUtilityValue(SPMiniMaxNode* node);


int getOptimalMoveFromNode(SPMiniMaxNode* node);

#endif

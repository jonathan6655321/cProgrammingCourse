
#ifndef SPMINIMAXNODE_H_
#define SPMINIMAXNODE_H_
#include "SPFIARGame.h"
#include "limits.h"
#include <assert.h>

typedef struct SPMiniMaxNode {
	SPFiarGame* game;
	int currentHeight;
	int utilityValue;
	struct SPMiniMaxNode* children[7];
} SPMiniMaxNode;

SPMiniMaxNode* spMiniMaxNodeCreate(SPFiarGame* game, int currentHeight);

void spMiniMaxNodeDestroy(SPMiniMaxNode* node);

int calculateGameUtilityValue(SPFiarGame* game);

int getNodeUtilityValue(SPMiniMaxNode* node);


int getOptimalMoveFromNode(SPMiniMaxNode* node);

#endif

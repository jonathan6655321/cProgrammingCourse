#include "SPFIARGame.h"
#include "limits.h"

#ifndef SPMINIMAXNODE_H_
#define SPMINIMAXNODE_H_

typedef struct MiniMaxNode {
	SPFiarGame* game;
	int currentHeight;
	int utilityValue;
	MiniMaxNode* children[7];
} MiniMaxNode;

MiniMaxNode* spMiniMaxNodeCreate(SPFiarGame* game, int currentHeight) {
	if (!game) {
		return 0;
	}
	MiniMaxNode* minimaxnode = calloc(sizeof(MiniMaxNode));
	if (!minimaxnode) {
		printf(FUNCTION_ERROR, "calloc");
		return 0;
	}
	minimaxnode->game = game;
	minimaxnode->currentHeight = currentHeight;

	if (currentHeight != 0) {
		for (int i = 0; i < 7; i++) {
			if (spFiarGameIsValidMove(game, i)) {
				SPFiarGame* spfiargame = spFiarGameCopy(game);
				if (!spfiargame) {
					continue;
				}
				spFiarGameSetMove(spfiargame, i);
				minimaxnode->children[i] = spMiniMaxNodeCreate(spfiargame,
						currentHeight - 1);
				if (!minimaxnode->children[i]) {
					spFiarGameDestroy(spfiargame);
				}
			}
		}
	}
	return minimaxnode;

}

void spMiniMaxNodeDestroy(MiniMaxNode* node) {
	for (int i = 0; i < 7; i++) {
		if (!(node->children[i])) {
			spMiniMaxNodeDestroy(node->children[i]);
		}
	}
	spFiarGameDestroy(node->game);
	free(node);
}

int calculateGameUtilityValue(SPFiarGame* game) {
	//=====================================================================
	return 0;
}

int getNodeUtilityValue(MiniMaxNode* node) {
	if (node->currentHeight == 0) {
		node->utilityValue = calculateGameUtilityValue(node->game);

	} else {
		int min = INT_MAX;
		int max = INT_MIN;
		int hasChildren = 0;
		int currentValue = 0;
		for (int i = 0; i < 7; i++) {
			if (!(node->children[i])) {
				hasChildren = 1;
				currentValue = getNodeUtilityValue(node->children[i]);
				min = (min > currentValue) ? currentValue : min;
				max = (max < currentValue) ? currentValue : max;
			}
		}
		if (!hasChildren) {
			node->utilityValue = calculateGameUtilityValue(node->game);
		} else {
			if (node->game->currentPlayer == 0) {
				node->utilityValue = max;
			} else {
				node->utilityValue = max;
			}
		}
	}
	return node->utilityValue;
}

int getOptimalMoveFromNode(MiniMaxNode* node) {
	int optimalValue = getNodeUtilityValue(node);
	for (int i = 0; i < 7; i++) {
		if(node->children[i]!=0 && node->children[i]->utilityValue == optimalValue){
			return i;
		}
	}
	return -1;
}
//Put all decleartions and constants here

#endif

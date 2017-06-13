
#ifndef SPMINIMAXNODE_H_
#define SPMINIMAXNODE_H_
#include "SPFIARGame.h"
#include "limits.h"

typedef struct SPMiniMaxNode {
	SPFiarGame* game;
	int currentHeight;
	int utilityValue;
	struct SPMiniMaxNode* children[7];
} SPMiniMaxNode;


/*
 * recursively defines the entire tree under this node, defining possible games along the way
 * returns pointer to the root
 *
 * note: should run this function with current Height = max height in order to get entire tree.
 */
SPMiniMaxNode* spMiniMaxNodeCreate(SPFiarGame* game, int currentHeight);

/*
 * recursively destroys this tree
 */
void spMiniMaxNodeDestroy(SPMiniMaxNode* node);


/*
 * calculation of a games value according to the criteria given in the assignment
 *
 * returns INT_MAX if winning state, INT_MIN for losing
 */
int calculateGameUtilityValue(SPFiarGame* game);

/*
 * helper functions for calculateGameUtilityValue
 *
 * they change spanScores in place. updating counts of -3,-2,-1,1,2,3 scored span counts
 * returns INT_MAX if winning state, INT_MIN for losing
 *
 * return 0 upon succesful finish
 */
int countHorizontalScore(SPFiarGame* game, int *spanScores);
int countVerticalScore(SPFiarGame* game, int *spanScores);
int countDiagonalScoreLeftToRight(SPFiarGame* game, int *spanScores);
int countDiagonalScoreRightToLeft(SPFiarGame* game, int *spanScores);





/*
 * a recursive function which calculates the utility value of all nodes, starting from this one.
 * we work with height instead of depth. 0 is a terminating state.
 *
 * returns the value calcualated.
 */
int getNodeUtilityValue(SPMiniMaxNode* node);


/*
 * returns integer between 0 and 6 according to the column to place the disc
 */
int getOptimalMoveFromNode(SPMiniMaxNode* node);

#endif

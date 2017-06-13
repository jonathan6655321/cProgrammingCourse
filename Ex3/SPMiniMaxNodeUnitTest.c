//#include "unit_test_util.h"
//#include "SPMiniMax.h"
////#include "SPMiniMaxNode.h"
//#include <stdbool.h>
//
//#define HISTORY_SIZE 20
//
//static bool scoringFunctionTest()
//{
//	SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
//	int val = calculateGameUtilityValue(res);
//	//printf("\n%d\n",val);
//	ASSERT_TRUE(val == 0);
//
//	spFiarGameSetMove(res,0);
//	val = calculateGameUtilityValue(res);
//	//printf("\n%d\n",val);
//	ASSERT_TRUE(val == 3);
//
//	spFiarGameSetMove(res,0);
//	val = calculateGameUtilityValue(res);
//	//printf("\n%d\n",val);
//	ASSERT_TRUE(val == -1);
//
//	spFiarGameSetMove(res,1);
//	val = calculateGameUtilityValue(res);
//	//printf("\n%d\n",val);
//	ASSERT_TRUE(val == 3);
//
//	spFiarGameSetMove(res,2);
//	val = calculateGameUtilityValue(res);
//	//printf("\n%d\n",val);
//	ASSERT_TRUE(val == -2);
//
//	spFiarGameDestroy(res);
//	return true;
//}
//
//static bool scoringFunctionTest2()
//{
//	SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
//
//	spFiarGameSetMove(res,1);
//	spFiarGameSetMove(res,5);
//	spFiarGameSetMove(res,1);
//	spFiarGameSetMove(res,1);
//	spFiarGameSetMove(res,1);
//	spFiarGameSetMove(res,6);
//	spFiarGameSetMove(res,1);
//	spFiarGameSetMove(res,3);
//	spFiarGameSetMove(res,4);
//	spFiarGameSetMove(res,3);
//	spFiarGameSetMove(res,2);
//	spFiarGameSetMove(res,2);
//	spFiarGameSetMove(res,3);
//	spFiarGameSetMove(res,2);
//
//	int val = calculateGameUtilityValue(res);
//	ASSERT_TRUE(val == -6);
//	spFiarGameDestroy(res);
//
//	return true;
//}
//
//static bool spMinimaxSuggestNodeTest() {
//	SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
//
//	for(int i=0;i<3;i++)
//	{
//		spFiarGameSetMove(res,i);
//		spFiarGameSetMove(res,i);
//	}
//	int val = spMinimaxSuggestMove(res, 5);
//	ASSERT_TRUE(val == INT_MAX);
//
//	spFiarGameSetMove(res,6);
//	val = spMinimaxSuggestMove(res, 5);
//	ASSERT_TRUE(val == -13);
//
//	spFiarGameDestroy(res);
//
//	return true;
//}
//
//int main() {
//	RUN_TEST(scoringFunctionTest);
//	RUN_TEST(scoringFunctionTest2);
//	RUN_TEST(spMinimaxSuggestNodeTest);
//
//	return 0;
//}

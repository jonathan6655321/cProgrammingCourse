#include "SPArrayList.h"

SPArrayList* spArrayListCreate(int maxSize) {
	SPArrayList* sparraylist = calloc(1,sizeof(SPArrayList)); // TODO
	if (!sparraylist) {
		printf(FUNCTION_ERROR, "calloc");
		abort();
	}
	sparraylist->maxSize = maxSize;
	sparraylist->actualSize = 0;
	sparraylist->elements = calloc(maxSize, sizeof(int)); // TODO
	if (!(sparraylist->elements)) {
		free(sparraylist);
		printf(FUNCTION_ERROR, "calloc");
		abort();
	}
	return sparraylist;
}

void spArrayListDestroy(SPArrayList* src) {
	free(src->elements);
	free(src);
}

SPArrayList* spArrayListCopy(SPArrayList* src) {
	SPArrayList* dest = spArrayListCreate(src->maxSize);
	if (!dest) {
		return 0;
	}
	while (src->actualSize != dest->actualSize) {
		dest->elements[dest->actualSize] = src->elements[dest->actualSize];
		dest->actualSize++;
	}
	return dest;
}

SP_ARRAY_LIST_MESSAGE spArrayListClear(SPArrayList* src) {
	if (!src) {
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	}
	src->actualSize = 0;
	return SP_ARRAY_LIST_SUCCESS;
}

void spArrayListShiftArrayRightByOne(SPArrayList* src, int index) {
	src->actualSize++;
	int shift_point = index + 1;
	while (shift_point < src->actualSize) { // move all elements
		src->elements[shift_point] = src->elements[shift_point - 1];
		shift_point++;
	}
}

bool spArrayListIsFull(SPArrayList* src) {
	return src->actualSize == src->maxSize;
}

SP_ARRAY_LIST_MESSAGE spArrayListAddAt(SPArrayList* src, int elem, int index) {
	if (!src || src->actualSize > index || index < 0) {
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	} else if (spArrayListIsFull(src)) {
		return SP_ARRAY_LIST_FULL;
	}
	spArrayListShiftArrayRightByOne(src, index);
	src->elements[index] = elem;
	return SP_ARRAY_LIST_SUCCESS;
}

SP_ARRAY_LIST_MESSAGE spArrayListAddFirst(SPArrayList* src, int elem) {
	if (!src) {
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	} else if (spArrayListIsFull(src)) {
		return SP_ARRAY_LIST_FULL;
	}
	spArrayListShiftArrayRightByOne(src, 0);
	src->elements[0] = elem;
	return SP_ARRAY_LIST_SUCCESS;
}

SP_ARRAY_LIST_MESSAGE spArrayListAddLast(SPArrayList* src, int elem) {
	if (!src) {
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	} else if (spArrayListIsFull(src)) {
		return SP_ARRAY_LIST_FULL;
	}
	src->actualSize++;
	src->elements[src->actualSize - 1] = elem;
	return SP_ARRAY_LIST_SUCCESS;
}

void spArrayListShiftArrayByMinusOne(SPArrayList* src, int index) {
	src->actualSize--;
	int shift_point = index;
	while (shift_point < src->actualSize) { // move all elements
		src->elements[shift_point] = src->elements[shift_point + 1];
		shift_point++;
	}
}

bool spArrayListIsEmpty(SPArrayList* src) {
	return src->actualSize == 0;
}

SP_ARRAY_LIST_MESSAGE spArrayListRemoveAt(SPArrayList* src, int index) {
	if (!src || index < 0 || index >= src->actualSize) {
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	} else if (spArrayListIsEmpty(src)) {
		return SP_ARRAY_LIST_EMPTY;
	}
	spArrayListShiftArrayByMinusOne(src, index);
	return SP_ARRAY_LIST_SUCCESS;
}

SP_ARRAY_LIST_MESSAGE spArrayListRemoveFirst(SPArrayList* src) {
	if (!src) {
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	} else if (spArrayListIsEmpty(src)) {
		return SP_ARRAY_LIST_EMPTY;
	}
	spArrayListShiftArrayByMinusOne(src, 0);
	return SP_ARRAY_LIST_SUCCESS;
}

SP_ARRAY_LIST_MESSAGE spArrayListRemoveLast(SPArrayList* src) {
	if (!src) {
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	} else if (spArrayListIsEmpty(src)) {
		return SP_ARRAY_LIST_EMPTY;
	}
//	printf("actual size before: %d\n", src->actualSize); TODO delete this
	src->actualSize--;
//	printf("actual size after: %d\n", src->actualSize); TODO delete this
	return SP_ARRAY_LIST_SUCCESS;
}

int spArrayListGetAt(SPArrayList* src, int index) {
	return src->elements[index];
}

int spArrayListGetFirst(SPArrayList* src) {
	return spArrayListGetAt(src, 0);
}

int spArrayListGetLast(SPArrayList* src) {
	return spArrayListGetAt(src, src->actualSize - 1);
}

int spArrayListMaxCapacity(SPArrayList* src) {
	return src->maxSize;
}

int spArrayListSize(SPArrayList* src) {
	return src->actualSize;
}

SP_ARRAY_LIST_MESSAGE spArrayListPush(SPArrayList* src, int elem){
	if (!src) {
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	} else if (spArrayListIsFull(src)) {
		spArrayListRemoveFirst(src);
	}
	return spArrayListAddLast(src, elem);
}

int spArrayListPop(SPArrayList* src){
	if (!src || spArrayListIsEmpty(src)) {
		return -1;
	}
	int ret = spArrayListGetLast(src);
	spArrayListRemoveLast(src);
	return ret;
}


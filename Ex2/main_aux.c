/*
 * main_aux.c
 *
 *  Created on: 27 ???? 2017
 *      Author: Ido Kessler & Jonathan Somer
 */

#include <stdio.h>
#include "SPBufferset.h"

#define MAX_NUMBER_OF_HEAPS 32
#define HEAP_REPRESENTATION "*"

#define GET_NUMBER_OF_HEAPS_STRING "Enter the number of heaps:\n"
#define GET_NUMBER_OF_HEAPS_ERROR "Error: the number of heaps must be between 1 and %d.\n"
#define GET_HEAPS_SIZES_STRING "Enter the heap sizes:\n"
#define GET_HEAPS_SIZES_ERROR_TOO_LOW "Error: the size of heap %d should be positive.\n"
#define TURN_INFO_STRING "In turn %d the heap sizes are: "

void print_turn_info(int turn, int number_of_heaps, int * heaps);
void print_heaps_visual(int number_of_heaps, int * heaps);
int max(int * array);
int initiate_heaps_by_user_input(int * number_of_heaps, int * heaps);
int get_number_of_heaps(int * number_of_heaps);
int get_heaps_sizes(int number_of_heaps, int * heaps);
int check_heaps(int number_of_heaps, int * heaps);

void print_turn_info(int turn, int number_of_heaps, int * heaps) {
	printf(TURN_INFO_STRING, turn);
	for (int i = 0; i < number_of_heaps; i++) {
		printf(" %d", heaps[i]);
	}
	printf('\n');
}

void print_heaps_visual(int number_of_heaps, int * heaps) {
	int max_heap = max(number_of_heaps, heaps);
	for (int line = max_heap; line > 0; line--) {
		if (heaps[0] >= line) {
			printf(HEAP_REPRESENTATION);
		}
		for (int i = 1; i < number_of_heaps; i++) {
			if (heaps[i] >= line) {
				printf('\t');
				printf(HEAP_REPRESENTATION);
			}
		}
		printf('\n');
	}
}

int max(int array_length, int * array) {
	int max_index = 0;
	int max_value = array[0];
	for (int i = 1; i < array_length; i++) {
		if (max_value < array[i]) {
			max_value = array[i];
			max_index = i;
		}
	}
	return max_value;
}

int initiate_heaps_by_user_input(int * number_of_heaps, int * heaps) {
	if (get_number_of_heaps(number_of_heaps) == 0) {
		return 0;
	}

	if (get_heaps_sizes(*number_of_heaps, heaps) == 0) {
		return 0;
	}

	return 1;
}

int get_number_of_heaps(int * number_of_heaps) {
	printf(GET_NUMBER_OF_HEAPS_STRING);
	scanf("%d", number_of_heaps);
	if (*number_of_heaps < 1 || *number_of_heaps > MAX_NUMBER_OF_HEAPS) {
		printf(GET_NUMBER_OF_HEAPS_ERROR, MAX_NUMBER_OF_HEAPS);
		return 0;
	}
	return 1;
}

int get_heaps_sizes(int number_of_heaps, int * heaps) {
	int array[number_of_heaps];
	heaps = array;
	printf(GET_HEAPS_SIZES_STRING);
	for (int i = 0; i < number_of_heaps; i++) {
		scanf("%d", &heaps[i]);
	}

	return check_heaps(number_of_heaps, heaps);
}

int check_heaps(int number_of_heaps, int * heaps) {
	for (int i = 0; i < number_of_heaps; i++) {
		if (heaps[i] < 0) {
			printf(GET_HEAPS_SIZES_ERROR_TOO_LOW, i + 1);
			return 0;
		}
	}
	return 1;
}


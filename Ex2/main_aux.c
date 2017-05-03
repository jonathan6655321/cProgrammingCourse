/*
 * main_aux.c
 *
 *  Created on: 27 ???? 2017
 *      Author: Ido Kessler & Jonathan Somer
 */

#include <stdio.h>

#define MAX_NUMBER_OF_HEAPS 32
#define HEAP_REPRESENTATION "*"
#define HEAP_NONE_REPRESENTATION " "

#define GET_NUMBER_OF_HEAPS_STRING "Enter the number of heaps:\n"
#define GET_NUMBER_OF_HEAPS_ERROR "Error: the number of heaps must be between 1 and %d.\n"
#define GET_HEAPS_SIZES_STRING "Enter the heap sizes:\n"
#define GET_HEAPS_SIZES_ERROR_TOO_LOW "Error: the size of heap %d should be positive.\n"
#define TURN_INFO_STRING "In turn %d heap sizes are:"
#define COMPUTER_TURN_STRING "Computer takes %d objects from heap %d.\n"
#define USER_TURN_STRING "You take %d objects from heap %d.\n"
#define USER_WIN_STRING "You win!\n"
#define COMPUTER_WIN_STRING "Computer wins!\n"

#ifndef __TYPES
#define __TYPES
	typedef enum {
		USER, COMPUTER
	} player;
	typedef struct {
		int number_of_object_taken;
		int heap_taken_from;
	} move;
#endif

void print_turn_info(int turn, int number_of_heaps, int heaps[]);
void print_heaps_visualization(int number_of_heaps, int heaps[]);
void print_win_message(player p);
int max(int array_length, int array[]);
int initiate_heaps_by_user_input(int * number_of_heaps, int heaps[]);
int set_number_of_heaps(int * number_of_heaps);
int set_heaps_sizes(int number_of_heaps, int heaps[]);
	void print_and_make_move(player p, move m, int heaps[]);

void print_turn_info(int turn, int number_of_heaps, int heaps[]) {
	printf(TURN_INFO_STRING, turn);
	for (int i = 0; i < number_of_heaps; i++) {
		printf(" h%d=%d", i + 1, heaps[i]);
	}
	printf(".\n");
}

void print_win_message(player p) {
	if (p == COMPUTER)
		printf(COMPUTER_WIN_STRING);
	else
		printf(USER_WIN_STRING);
}

void print_heaps_visualization(int number_of_heaps, int heaps[]) {
	int max_heap = max(number_of_heaps, heaps);
	for (int line = max_heap; line > 0; line--) {
		if (heaps[0] >= line) {
			printf(HEAP_REPRESENTATION);
		}else{
			printf(HEAP_NONE_REPRESENTATION);
		}
		for (int i = 1; i < number_of_heaps; i++) {
			printf("\t");
			if (heaps[i] >= line) {
				printf(HEAP_REPRESENTATION);
			}else{
				printf(HEAP_NONE_REPRESENTATION);
			}
		}
		printf("\n");
	}
}

int max(int array_length, int array[]) {
	int max_value = array[0];
	for (int i = 1; i < array_length; i++) {
		if (max_value < array[i]) {
			max_value = array[i];
		}
	}
	return max_value;
}

void print_and_make_move(player p, move m, int heaps[]) {
	heaps[m.heap_taken_from - 1] -= m.number_of_object_taken;

	if (p == COMPUTER)
		printf(COMPUTER_TURN_STRING, m.number_of_object_taken, m.heap_taken_from);
	else
		printf(USER_TURN_STRING, m.number_of_object_taken, m.heap_taken_from);
}

int initiate_heaps_by_user_input(int * number_of_heaps, int heaps[]) {
	if (set_number_of_heaps(number_of_heaps) == 0) {
		return 0;
	}

	if (set_heaps_sizes(*number_of_heaps, heaps) == 0) {
		return 0;
	}

	return 1;
}

int set_number_of_heaps(int * number_of_heaps) {
	printf(GET_NUMBER_OF_HEAPS_STRING);
	scanf("%d", number_of_heaps);
	if (*number_of_heaps < 1 || *number_of_heaps > MAX_NUMBER_OF_HEAPS) {
		printf(GET_NUMBER_OF_HEAPS_ERROR, MAX_NUMBER_OF_HEAPS);
		return 0;
	}
	return 1;
}

int set_heaps_sizes(int number_of_heaps, int heaps[]) {
	printf(GET_HEAPS_SIZES_STRING);
	for (int i = 0; i < number_of_heaps; i++) {
		scanf("%d", &heaps[i]);
		if(heaps[i] < 0){
			printf(GET_HEAPS_SIZES_ERROR_TOO_LOW, i + 1);
			return 0;
		}
	}
	return 1;
}

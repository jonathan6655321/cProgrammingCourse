/*
 * sp_min.c
 *
 *  Created on: 27 ???? 2017
 *      Author: Ido Kessler & Jonathan Somer
 */

#include <stdio.h>

#define GET_USER_MOVE_STRING "Your turn: please enter the heap index and the number of removed objects.\n"
#define GET_USER_MOVE_STRING_ERROR "Error: Invalid input.\nPlease enter again the heap index and the number of removed objects.\n"

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

int heap_is_empty(int number_of_heaps, int heaps[]);
move get_move(player p, int number_of_heaps, int heaps[]);
move get_move_computer(int number_of_heaps, int heaps[]);
move get_move_user(int number_of_heaps, int heaps[]);
int is_valid_move(move m, int number_of_heaps, int heaps[]);
int calculate_nim_sum(int number_of_heaps, int heaps[]);
int min_not_empty_heap_index(int number_of_heaps, int heaps[]);
move get_computer_best_move(int nim_sum, int number_of_heaps, int heaps[]);
int is_winning_heap(int nim_sum, int heap_size);

int heap_is_empty(int number_of_heaps, int heaps[]) {
	int res = 1;
	for (int i = 0; i < number_of_heaps; i++) {
		res = res && (heaps[i] == 0);
	}
	return res;
}

move get_move(player p, int number_of_heaps, int heaps[]) {
	if (p == COMPUTER)
		return get_move_computer(number_of_heaps, heaps);
	else
		return get_move_user(number_of_heaps, heaps);
}

move get_move_user(int number_of_heaps, int heaps[]) {
	printf(GET_USER_MOVE_STRING);
	move m;
	m.heap_taken_from = 0;
	m.number_of_object_taken = 0;
	while (scanf("%d %d", &m.heap_taken_from, &m.number_of_object_taken) != 2
			|| !is_valid_move(m, number_of_heaps, heaps)) {
		printf(GET_USER_MOVE_STRING_ERROR);
		fflush(stdin);
	}
	return m;
}

int is_valid_move(move m, int number_of_heaps, int heaps[]) {
	if (m.heap_taken_from > number_of_heaps || m.heap_taken_from < 1) {
		return 0;
	} else if (m.number_of_object_taken > heaps[m.heap_taken_from - 1] || m.number_of_object_taken < 1)
		return 0;
	return 1;
}

move get_move_computer(int number_of_heaps, int heaps[]) {
	int nim_sum = calculate_nim_sum(number_of_heaps, heaps);
	if (nim_sum == 0) {
		move m;
		m.number_of_object_taken = 1;
		m.heap_taken_from = min_not_empty_heap_index(number_of_heaps, heaps)
				+ 1;
		return m;
	} else {
		return get_computer_best_move(nim_sum, number_of_heaps, heaps);
	}
}

int calculate_nim_sum(int number_of_heaps, int heaps[]) {
	int res = 0;
	for (int i = 0; i < number_of_heaps; i++) {
		res = res ^ heaps[i];
	}
	return res;
}

int min_not_empty_heap_index(int number_of_heaps, int heaps[]) {
	int min_index = -1;
	int min_value = 2147483647;
	for (int i = 0; i < number_of_heaps; i++) {
		if (heaps[i] != 0 && heaps[i] < min_value) {
			min_index = i;
			min_value = heaps[i];
		}
	}
	return min_index;
}

move get_computer_best_move(int nim_sum, int number_of_heaps, int heaps[]) {
	move m;
	for (int i = 0; i < number_of_heaps; i++) {
		if (is_winning_heap(nim_sum, heaps[i])) {
			m.heap_taken_from = i + 1;
			m.number_of_object_taken = heaps[i] - (heaps[i] ^ nim_sum);
			return m;
		}
	}
	return m;
}

int is_winning_heap(int nim_sum, int heap_size) {
	return (nim_sum ^ heap_size) < heap_size;
}


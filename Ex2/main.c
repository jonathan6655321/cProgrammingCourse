/*
 * main.c
 *
 *  Created on: 27 ???? 2017
 *      Author: Ido Kessler & Jonathan Somer
 */

#include <stdio.h>
#include "SPBufferset.h"

#define MAX_NUMBER_OF_HEAPS 32

typedef enum {
	USER, COMPUTER
} player;
typedef struct {
	int number_of_object_taken;
	int heap_taken_from;
} move;

int initiate_heaps_by_user_input(int * number_of_heaps, int heaps[]);
int heap_is_empty(int number_of_heaps, int heaps[]);
void print_turn_info(int turn, int number_of_heaps, int heaps[]);
void print_heaps_visualization(int number_of_heaps, int heaps[]);
void print_win_message(player p);
void print_and_make_move(player p, move m, int heaps[]);
move get_move(player p, int number_of_heaps, int  heaps[]);

int heaps[MAX_NUMBER_OF_HEAPS];
int number_of_heaps;
int turn;

int main(void) {
	SP_BUFF_SET();
	if (initiate_heaps_by_user_input(&number_of_heaps, heaps)) {
		turn = 1;
		player current_player = COMPUTER;
		while (!heap_is_empty(number_of_heaps, heaps)) {
			print_turn_info(turn, number_of_heaps, heaps);
			if (current_player == USER)
				print_heaps_visualization(number_of_heaps, heaps);

			print_and_make_move(current_player,
					get_move(current_player, number_of_heaps, heaps), heaps);

			current_player = (current_player == COMPUTER) ? USER : COMPUTER;
			turn++;
		}
		current_player = (current_player == COMPUTER) ? USER : COMPUTER;
		print_win_message(current_player);
	}
}


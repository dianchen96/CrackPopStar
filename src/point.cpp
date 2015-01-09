#include "game.h"

struct pile formoves[SIZE][SIZE];

void setformoves() {
	int i, j;
	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++) {
			formoves[i][j].x = i;
			formoves[i][j].y = j;
		}
}

struct pile *givepointer(int x, int y) {
	return &formoves[x][y];
}
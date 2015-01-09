#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include "game.h"

char piles[SIZE][SIZE]= 
{{P,B,P,P,R,Y,G,P,R,G},
 {R,Y,B,P,R,B,G,P,R,G},
 {B,R,B,Y,R,Y,G,G,Y,R},
 {G,Y,R,G,R,Y,B,Y,G,G},
 {Y,B,G,R,B,R,Y,G,R,G},
 {B,B,P,B,P,R,B,P,G,G},
 {Y,P,B,Y,Y,R,P,R,Y,Y},
 {B,B,P,Y,B,R,R,R,Y,R},
 {Y,G,Y,G,Y,R,R,Y,P,G},
 {Y,R,B,G,B,Y,Y,B,R,Y}};
 
int piles_dir[SIZE][SIZE];
struct pile blocks[2*PILENUM];
struct pile *p = blocks; 

std::string result;

int times = 0;

struct move finalmove = {0, 0, 0};

void think(char[SIZE][SIZE], struct pile[PILENUM], struct move*, int);
void findbest(struct move*);



int main() {
	int i ,j;
	char *pp = &piles[0][0];
	/*
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			while(printf("row %d, column %d£∫ ", i, j) && getpile(pp) == 0)
				;
			pp++;
		}
	}
	*/

	printf("\nInput is complete, please comfirm:\n");
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			printf(" %c", piles[i][j]);
		}
		printf("\n");
	}

	
	dirscan(piles, piles_dir);
	
	/*≤‚ ‘”√
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			printf(" %d", piles_dir[i][j]);
		}
		printf("\n");
	}
	*/

	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			toblocks(i, j, piles_dir);
			ridzeros(piles_dir);
			if ((p-1)->x != -1) {
				p->x = -1;
			    p->y = -1;
			    p++;
			}
		}
	}
	p->x = SIZE;
    struct move *root = new struct move;
	root->lastmove = 0;
	root->point = 0;
	root->totalpoints = 0;

	/*≤‚ ‘”√
	for (i = 0; blocks[i].x!=SIZE; i++) {
		if (blocks[i].x == -1)
			printf("\n");
		else 
			printf(" %d,%d", blocks[i].x, blocks[i].y);
	}
	*/
	setformoves();
	think(piles, blocks, root, 0);

	printf("the best result is %d\n", finalmove.totalpoints);
	findbest(&finalmove);

	std::cout << result << std::endl;
	
	return 0;
	
	
}




void show() {
	int i, j;
	printf("\n");
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			printf(" %d", piles_dir[i][j]);
		}
		printf("\n");
	}
}


void findbest(struct move *lastmove) {
	if (lastmove->point == NULL)
		return;
	
	char *x = new char[5];
	char *y = new char[5];
	std::string strx, stry;
	_itoa(lastmove->point->x, x, 10);
	_itoa(lastmove->point->y, y, 10);
	strx = x;
	stry = y;
	delete[] x;
	delete[] y;
	result = " "+strx+","+stry+result;
	
	findbest(lastmove->lastmove);
}
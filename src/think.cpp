#include "game.h"
#include <stdio.h>
#include <stdlib.h>


char temp_pile[SIZE][SIZE];
extern struct move finalmove;

extern struct pile *p;

extern int times;

int isfinal(int[SIZE][SIZE]);
int getbonus(char[SIZE][SIZE]);
void prune(struct pile[2*PILENUM],char[SIZE][SIZE]);
int potent(char[SIZE][SIZE]);

void think(char origin_p[SIZE][SIZE], struct pile origin_b[2*PILENUM], struct move *lastmove, int depth) {
	if (times > MAX)
		return;

	struct pile *cp = origin_b;
	struct pile **op = &cp;
	char (*curr_p)[SIZE] = (char (*)[SIZE])new char[PILENUM];

	makecopy(curr_p, origin_p);
	int points;
	while (makecopy(curr_p, origin_p) && (points = simulate(curr_p, op)) > 0) {
		/*测试用	
		for (int i = 0; i < SIZE; i++) {
		    for (int j = 0; j < SIZE; j++){
			    printf(" %c", curr_p[i][j]);
		    }
		    printf("\n");
	    }
		*/
		/*设置move*/

	    struct move *movep = new struct move;
		movep->point = givepointer((((*op)-1)->x),(((*op)-1)->y));
		
	    movep->lastmove = lastmove;
		movep->totalpoints = lastmove->totalpoints + points;
		
		
			
	    int (*pile_dir)[SIZE] = (int(*)[SIZE]) new int[PILENUM];
		dirscan(curr_p, pile_dir);
		if (isfinal(pile_dir)) {
			delete[] (int*)pile_dir;
			movep->totalpoints += getbonus(curr_p);
			if ((movep->totalpoints) > finalmove.totalpoints) {
				finalmove = *movep;
				printf("calc a new final\n");
		    }
			return;
		}
		/*测试用
		for (int i = 0; i < SIZE; i++) {
		    for (int j = 0; j < SIZE; j++) {
			    printf(" %d", pile_dir[i][j]);
		    }
		    printf("\n");
	    }
		*/

	    struct pile *curr_b = new struct pile[2*PILENUM];
		p = curr_b;
			
		for (int i = 0; i < SIZE; i++) {
		    for (int j = 0; j < SIZE; j++) {
			     toblocks(i, j, pile_dir);
			     ridzeros(pile_dir);
			     if ((p-1)->x != -1) {
				     p->x = -1;
			         p->y = -1;
			         p++;
			     }
		    }
	    }
		p->x = SIZE;       /*放置断点*/  
	    delete[] (int*)pile_dir;
		
		/*测试用
	    for (int i = 0; curr_b[i].x!=SIZE; i++) {
		    if (curr_b[i].x == -1)
			    printf("\n");
		    else 
			    printf(" %d,%d", curr_b[i].x, curr_b[i].y);
	    }
		*/
		times++;
	    think(curr_p, curr_b, movep, ++depth);
		delete[] curr_b;
		
	}
	
	delete[] (char*)curr_p;
}

int makecopy(char temp_p[SIZE][SIZE], char origin_p[SIZE][SIZE]) {
	int i, j;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			temp_p[i][j] = origin_p[i][j];
		}
	}
	return 1;
}

int simulate(char temp_p[SIZE][SIZE], struct pile **p) {
	int count = 0; 
	while ((*p)->x == -1)
		(*p)++;
	while ((*p)->x != -1) {
		if ((*p)->x == SIZE)
			return -1;
		else {
			count++;
		    (*p)++;
		}
    }
	int i, j, k;

	for (i = 0; i < count; i++) {
		temp_p[((*p)-count+i)->x][((*p)-count+i)->y] = 0;
	}
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			if (temp_p[j][i] == 0) {
				for (k = j; k > 0; k--) 
					temp_p[k][i] = temp_p[k-1][i];
				temp_p[0][i] = 0;
			}
		}
	}


	for (i = 0; i < SIZE; i++) {
		int zcount = 0;
		for (j = 0; j < SIZE; j++) {
			if (temp_p[j][i] == 0)
				zcount++;
		}
		if (zcount == SIZE) {
			int m;
			for (k = i+1; k < SIZE; k++)
				for (m = 0; m < SIZE; m++) {
					if (temp_p[m][k]==0)
						zcount++;
					else
						k = m = SIZE;
				}
			int x = zcount / SIZE;
			for (k = i; k < SIZE-x; k++) {
				for (m = 0; m < SIZE; m++)
					temp_p[m][k] = temp_p[m][k+x];
			}
			for (m = 0; m < SIZE; m++)
				for (k = 0; k < x; k++)
					temp_p[m][SIZE-1-k] = 0;

		}
	}

	return points(count);

}



int isfinal(int pile_dir[SIZE][SIZE]) {
	int i, j, count;
	count = 0;
	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
			if (pile_dir[i][j] == -1)
				count++;
	return (count == PILENUM)? 1: 0;
    
}

int getbonus(char pile[SIZE][SIZE]) {
	int i, j, count = 0;
	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
			if (pile[i][j] != 0)
				count++;
	return (count < 10)? bonus(count): 0;
}


void prune(struct pile blocks[2*PILENUM], char pile[SIZE][SIZE]) {
	struct pile *cp = blocks;
	struct pile **op = &cp;
	char (*curr_p)[SIZE] = (char (*)[SIZE])new char[PILENUM];

	makecopy(curr_p, pile);
	int points, max = 0, temp;
	struct pile *maxstr, *maxend;
	while (makecopy(curr_p, pile) && (points = simulate(curr_p, op)) > 0) {
		if ((temp = points + potent(curr_p)) > max) {
			max = temp;
			maxstr = maxend = *op;
			while (--maxstr >= blocks)
				if (maxstr->x == -1)
					break;
		}
	}
	for (struct pile *i = blocks; i->x != SIZE; i++) {
		if (i < maxstr || i > maxend)
			i->x = -1;
	}
	delete[] (char*)curr_p;
}


int potent(char pile[SIZE][SIZE]) {
	int (*pile_dir)[SIZE] = (int(*)[SIZE]) new int[PILENUM];
	dirscan(pile, pile_dir);

	struct pile *curr_b = new struct pile[2*PILENUM];
    p = curr_b;
	int i, result, count;
	result = count = 0;

	for (i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
			toblocks(i, j, pile_dir);
			ridzeros(pile_dir);
			if ((p-1)->x != -1) {
			    p->x = -1;
			    p->y = -1;
			    p++;
			}
		}
	}
    p->x = SIZE;       /*放置断点*/  
	delete[] (int*)pile_dir;
	for (i = 0; curr_b[i].x != SIZE; i++) {
		if (curr_b[i].x != -1)
			count++;
		else {
			result += points(count);
			count = 0;
		}
	}
	delete[] curr_b;
	return result;
}
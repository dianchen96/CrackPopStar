#include <stdio.h>
#include "game.h"

extern struct pile *p;



void dirscan(char a[SIZE][SIZE], int piles_dir[SIZE][SIZE]) {
	int i, j;
	for (i = 0; i < SIZE; i++) 
		for (j = 0; j < SIZE; j++) 
			piles_dir[i][j] = connected(i, j, a);

}

int connected(int x, int y, char piles[SIZE][SIZE]) {
	int color, result = 0;
	if ((color = piles[x][y]) == 0)
		return -1;
	if (x > 0 && color == piles[x-1][y])
		result += 3;
	if (y > 0 && color == piles[x][y-1])
		result += 5;
	if (x < SIZE-1 && color == piles[x+1][y])
		result += 6;
	if (y < SIZE-1 && color == piles[x][y+1])
		result += 7;
	if (result == 0)
		return -1;
	return result;
}



void toblocks(int x, int y, int piles_dir[SIZE][SIZE]) {
	int dirnum = piles_dir[x][y];

	switch (dirnum) {
	case 0:
		p->x = x;
		p->y = y;
		p++;
		piles_dir[x][y] = -1;
		return;
	case 3:
		piles_dir[x][y] = 0;
		piles_dir[x-1][y] -= 6;
		p->x = x;
		p->y = y;
		p++;
		toblocks(x-1, y, piles_dir);
		break;
	case 5:
		piles_dir[x][y] = 0;
		piles_dir[x][y-1] -= 7;
		p->x = x;
		p->y = y;
		p++;
		toblocks(x, y-1, piles_dir);
		break;
	case 6:
		piles_dir[x][y] = 0;
		piles_dir[x+1][y] -= 3;
		p->x = x;
		p->y = y;
		p++;
		toblocks(x+1, y, piles_dir);
		break;
	case 7:
		piles_dir[x][y] = 0;
		piles_dir[x][y+1] -= 5;
		p->x = x;
		p->y = y;
		p++;
		toblocks(x, y+1, piles_dir);
		break;
	case 8:
		piles_dir[x][y] = 0;
		piles_dir[x-1][y] -= 6;
		piles_dir[x][y-1] -= 7;
		p->x = x;
		p->y = y;
		p++;
		toblocks(x-1, y, piles_dir);
		toblocks(x, y-1, piles_dir);
		break;
	case 9:
		piles_dir[x][y] = 0;
		piles_dir[x-1][y] -= 6;
		piles_dir[x+1][y] -= 3;
		p->x = x;
		p->y = y;
		p++;
		toblocks(x-1, y, piles_dir);
		toblocks(x+1, y, piles_dir);
		break;
    case 10:
		piles_dir[x][y] = 0;
		piles_dir[x-1][y] -= 6;
		piles_dir[x][y+1] -= 5;
		p->x = x;
		p->y = y;
		p++;
		toblocks(x-1, y, piles_dir);
		toblocks(x+1, y, piles_dir);
		break;
	case 11:
		piles_dir[x][y] = 0;
		piles_dir[x+1][y] -= 3;
		piles_dir[x][y-1] -= 7;
		p->x = x;
		p->y = y;
		p++;
		toblocks(x+1, y, piles_dir);
		toblocks(x, y-1, piles_dir);
		break;
	case 12:
		piles_dir[x][y] = 0;
		piles_dir[x][y+1] -= 5;
		piles_dir[x][y-1] -= 7;
		p->x = x;
		p->y = y;
		p++;
		toblocks(x, y+1, piles_dir);
		toblocks(x, y-1, piles_dir);
		break;
	case 13:
		piles_dir[x][y] = 0;
		piles_dir[x][y+1] -= 5;
		piles_dir[x+1][y] -= 3;
		p->x = x;
		p->y = y;
		p++;
		toblocks(x, y+1, piles_dir);
		toblocks(x+1, y, piles_dir);
		break;
	case 14:
		piles_dir[x][y] = 0;
		piles_dir[x-1][y] -= 6;
		piles_dir[x][y-1] -= 7;
		piles_dir[x+1][y] -= 3;
		p->x = x;
		p->y = y;
		p++;
		toblocks(x-1, y, piles_dir);
		toblocks(x, y-1, piles_dir);
		toblocks(x+1, y, piles_dir);
		break;
	case 15:
		piles_dir[x][y] = 0;
		piles_dir[x-1][y] -= 6;
		piles_dir[x][y-1] -= 7;
		piles_dir[x][y+1] -= 5;
		p->x = x;
		p->y = y;
		p++;
		toblocks(x-1, y, piles_dir);
		toblocks(x, y-1, piles_dir);
		toblocks(x, y+1, piles_dir);
		break;
	case 16:
		piles_dir[x][y] = 0;
		piles_dir[x-1][y] -= 6;
		piles_dir[x+1][y] -= 3;
		piles_dir[x][y+1] -= 5;
		p->x = x;
		p->y = y;
		p++;
		toblocks(x-1, y, piles_dir);
		toblocks(x+1, y, piles_dir);
		toblocks(x, y+1, piles_dir);
		break;
	case 18:
		piles_dir[x][y] = 0;
		piles_dir[x][y+1] -= 5;
		piles_dir[x][y-1] -= 7;
		piles_dir[x+1][y] -= 3;
		p->x = x;
		p->y = y;
		p++;
		toblocks(x, y-1, piles_dir);
		toblocks(x, y+1, piles_dir);
		toblocks(x+1, y, piles_dir);
		break;
	default:
		if ((p-1)->x != -1) {
			p->x = -1;
			p->y = -1;
			p++;
		}
		break;
	}


}

void ridzeros(int piles_dir[SIZE][SIZE]) {
	int i, j;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			if (piles_dir[i][j] == 0)
				piles_dir[i][j] = -1;
		}
	}
}



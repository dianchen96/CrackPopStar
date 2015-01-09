#include <stdio.h>
#include "game.h"


int getpile(char *p) {
	int c = getchar();
	while(getchar()!='\n')
		;
	if (c == 'r'||c == 'g'||c == 'b'||c == 'y'||c == 'p') {
		*p = c;
		return c;
	} 
	else {
		printf("Error: invalid color\n");
		return 0;
	}
}


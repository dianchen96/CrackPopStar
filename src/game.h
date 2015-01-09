#define SIZE 10
#define PILENUM (SIZE*SIZE)
#define MAX 1000000

#define points(n) (5*n*n)
#define bonus(n) (2000-20*n*n)

#define R 'r'
#define G 'g'
#define B 'b'
#define Y 'y'
#define P 'p'

struct pile {
	short x;
	short y;
};

struct move {
	int totalpoints;
	struct pile *point;
	struct move *lastmove;
};

int getpile(char *);


int connected(int, int, char[SIZE][SIZE]);
void dirscan(char[SIZE][SIZE], int[SIZE][SIZE]);
void toblocks(int, int, int[SIZE][SIZE]);
void ridzeros(int[SIZE][SIZE]);
void show(void);  /*≤‚ ‘”√*/

int simulate(char[SIZE][SIZE], struct pile**); 
int makecopy(char[SIZE][SIZE], char[SIZE][SIZE]);

void setformoves(void);
struct pile *givepointer(int, int);
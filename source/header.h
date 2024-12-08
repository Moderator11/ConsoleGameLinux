#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <curses.h>
#include <time.h>
#include <ncursesw/curses.h>
#include <locale.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>

// start.c
#define START_LIMIT 1
#define END_LIMIT 4

#define START_POS 1

// main_PingPong.c
#define	BLANK		' '
#define	DFL_SYMBOL	'o'

#define	TOP_ROW		0
#define	BOT_ROW 	(24 - 10)
#define	LEFT_EDGE	0
#define	RIGHT_EDGE	80

#define	TICKS_PER_SEC 50

struct ppball {
    float position_y;
    float position_x;
    float velocity_y;
    float velocity_x;
	char	symbol ;
} ;

int set_ticker(int);
void Initialize();
void CleanUp();
void ball_move(int);
void HandleInput();

// breakout.c
#define WIDTH 40
#define HEIGHT 20
#define PADDLE_WIDTH 7 // the horizontal thingy that hits the ball
#define BALL_SPEED 90000 // the higher the slower

#define BRICK '#'
#define BRICK_ROWS 2 // number of brick rows

typedef struct {
    int x, y; // position of the ball
    int dx, dy; // change in position
} Ball;

typedef struct {
    int x;
} Paddle;

void init_game(Ball *, Paddle *, int [BRICK_ROWS][WIDTH], int *);
void draw_game(Ball *, Paddle *, int[BRICK_ROWS][WIDTH], int);
void update_game(Ball *, Paddle *, int [BRICK_ROWS][WIDTH], int *, int *);
void handle_input(Paddle *);
void start_game();

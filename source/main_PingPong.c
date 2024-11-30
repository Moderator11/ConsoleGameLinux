#pragma region Declaration

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <curses.h>
#include <time.h>

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

struct ppball ball;
float bounceCoeff = 0.95;

float wall_1_x = RIGHT_EDGE * 0.8;
float wall_1_y = BOT_ROW / 2;

float wall_2_x = RIGHT_EDGE * 0.2;
float wall_2_y = BOT_ROW / 2;

int gameOver = false;

#pragma endregion Declaration

#pragma region Logics

int set_ticker( int n_msecs )
{
	struct itimerval new_timeset;
	long    n_sec, n_usecs;
	n_sec = n_msecs / 1000 ;		/* int part*/
	n_usecs = ( n_msecs % 1000 ) * 1000L ;  /* remainder*/

	new_timeset.it_interval.tv_sec = n_sec;		/* set reload */
	new_timeset.it_interval.tv_usec = n_usecs;  /* new ticker value */
	new_timeset.it_value.tv_sec     = n_sec;	/* store this */
	new_timeset.it_value.tv_usec    = n_usecs;	/* and this */

	return setitimer(ITIMER_REAL, &new_timeset, NULL);
}

void Initialize()
{
    gameOver = false;
    erase();
    srand(time(NULL));
    void	ball_move(int);
	ball.position_y = BOT_ROW / 2;
	ball.position_x = RIGHT_EDGE / 2;
	ball.velocity_y = 0;
	ball.velocity_x = 0.25 * (rand() % 2 == 0 ? -1 : 1);
	ball.symbol = DFL_SYMBOL ;

    wall_1_x = RIGHT_EDGE * 0.8;
    wall_1_y = BOT_ROW / 2;
    wall_2_x = RIGHT_EDGE * 0.2;
    wall_2_y = BOT_ROW / 2;

	initscr();
	noecho();
	crmode();

	signal( SIGINT , SIG_IGN );
    for (int x = 0; x < RIGHT_EDGE; x++)
    {
	    mvaddch( BOT_ROW, x, '*');
    }
    
	refresh();

	signal( SIGALRM, ball_move );
	set_ticker( 1000 / TICKS_PER_SEC ); /* send millisecs per tick */
}

void CleanUp()
{
	set_ticker( 0 );
	endwin();
}

void ball_move(int signum)
{	
	signal( SIGALRM , SIG_IGN );

    static float previous_position_y = 0;
	static float previous_position_x = 0;

    //====Physics
    ball.position_y += ball.velocity_y;
    ball.position_x += ball.velocity_x;
    ball.velocity_y += 0.00981;

    if(ball.position_y < TOP_ROW) {
        ball.position_y = TOP_ROW + 1;
        ball.velocity_y *= -bounceCoeff;
    } else if (ball.position_y > BOT_ROW) {
        ball.position_y = BOT_ROW - 1;
        ball.velocity_y *= -bounceCoeff;
    }
    if(ball.position_x < LEFT_EDGE) {
        ball.position_x = LEFT_EDGE + 1;
        ball.velocity_x *= -bounceCoeff;
    } else if (ball.position_x > RIGHT_EDGE) {
        ball.position_x = RIGHT_EDGE - 1;
        ball.velocity_x *= -bounceCoeff;
    }

    if(ball.position_x >= wall_1_x - 1
    && ball.position_x <= wall_1_x + 1
    && ball.position_y >= wall_1_y - 2
    && ball.position_y <= wall_1_y + 2) {
        ball.velocity_x *= -1.01;
    } else if(ball.position_x >= wall_2_x - 1
    && ball.position_x <= wall_2_x + 1
    && ball.position_y >= wall_2_y - 2
    && ball.position_y <= wall_2_y + 2) {
        ball.velocity_x *= -1.01;
    }

    if(gameOver == 0) {
        if(ball.position_x >= wall_1_x + 1) {
            mvaddstr((int)(BOT_ROW * 1.2), (int)(RIGHT_EDGE * 0.2), "player 1 win");
            gameOver = 1;
        }
        else if(ball.position_x <= wall_2_x - 1) {
            mvaddstr((int)(BOT_ROW * 1.2), (int)(RIGHT_EDGE * 0.8), "player 2 win");
            gameOver = 1;
        }
    }
    if(gameOver == 1) {
        mvaddstr((int)(BOT_ROW * 1.5), (int)(RIGHT_EDGE * 0.375), "Press r to restart");
    }
    //====Physics
    for (int y = -2; y < 3; y++)
    {
        for (int x = -1; x < 2; x++)
        {  
            if(wall_1_y + y == BOT_ROW) continue;
            mvaddch( wall_1_y + y, wall_1_x + x, BLANK);
            mvaddch( wall_2_y + y, wall_2_x + x, BLANK);
        }
    }

    for (int y = -1; y < 2; y++)
    {
        mvaddch( wall_1_y - y, wall_1_x, '|');
        mvaddch( wall_2_y - y, wall_2_x, '|');
    }

    for (int x = 0; x < RIGHT_EDGE; x++)
    {
	    mvaddch( BOT_ROW, x, '*');
    }
    

    mvaddch( previous_position_y, previous_position_x, BLANK );
	mvaddch( ball.position_y, ball.position_x, ball.symbol );
	move(LINES-1,COLS-1);
	refresh();

    previous_position_y = ball.position_y;
    previous_position_x = ball.position_x;
	
	signal( SIGALRM, ball_move);	/* for unreliable systems */
}

#pragma endregion Logics

#pragma region Main

void StartUpScreen() {
    system("clear");
    printf("WASD : Move Player1\n");
    printf("IJKL : Move Player2\n");
    printf("q : Quit\n");
    printf("Press enter to start.\n");
    getchar();
}

void HandleInput() {
    char c;
	while ( (c = getchar()) != 'q' ) {
        switch(c) {
            case 'w':
            if(wall_2_y - 2 >= 0)
            wall_2_y += -1;
            break;
            case 'a':
            if(wall_2_x - 1 >= 0)
            wall_2_x += -1;
            break;
            case 'd':
            if(wall_2_x + 1 <= RIGHT_EDGE * 0.5)
            wall_2_x += 1;
            break;
            case 's':
            if(wall_2_y + 3 <= BOT_ROW)
            wall_2_y += 1;
            break;

            case 'i':
            if(wall_1_y - 2 >= 0)
            wall_1_y += -1;
            break;
            case 'j':
            if(wall_1_x - 1 >= RIGHT_EDGE * 0.5)
            wall_1_x += -1;
            break;
            case 'l':
            if(wall_1_x + 1 <= RIGHT_EDGE)
            wall_1_x += 1;
            break;
            case 'k':
            if(wall_1_y + 3 <= BOT_ROW)
            wall_1_y += 1;
            break;

            case 'r':
            CleanUp();
            Initialize();
            break;
        }
	}
}

int main(void)
{
    StartUpScreen();
	Initialize();
    HandleInput();
	CleanUp();

	return 0;
}

#pragma endregion Main

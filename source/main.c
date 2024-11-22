#pragma region Declaration

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <curses.h>

#define	BLANK		' '
#define	DFL_SYMBOL	'o'

#define	TOP_ROW		0
#define	BOT_ROW 	24
#define	LEFT_EDGE	0
#define	RIGHT_EDGE	80

#define	TICKS_PER_SEC 50

struct ppball {
    float position_x;
    float position_y;
    float velocity_x;
    float velocity_y;
	char	symbol ;
} ;

struct ppball ball;
float bounceCoeff = 0.8;

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
    void	ball_move(int);
	ball.position_x = BOT_ROW / 2;
	ball.position_y = RIGHT_EDGE / 2;
	ball.velocity_x = 0;
	ball.velocity_y = 0.2;
	ball.symbol = DFL_SYMBOL ;
	initscr();
	noecho();
	crmode();

	signal( SIGINT , SIG_IGN );
	mvaddch( ball.position_x, ball.position_y, ball.symbol  );
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

    static float previous_position_x = 0;
	static float previous_position_y = 0;

    //====Physics
    ball.position_x += ball.velocity_x;
    ball.position_y += ball.velocity_y;
    ball.velocity_x += 0.00981;

    if(ball.position_x < TOP_ROW) {
        ball.position_x = TOP_ROW + 1;
        ball.velocity_x *= -bounceCoeff;
    } else if (ball.position_x > BOT_ROW) {
        ball.position_x = BOT_ROW - 1;
        ball.velocity_x *= -bounceCoeff;
    }
    if(ball.position_y < LEFT_EDGE) {
        ball.position_y = LEFT_EDGE + 1;
        ball.velocity_y *= -bounceCoeff;
    } else if (ball.position_y > RIGHT_EDGE) {
        ball.position_y = RIGHT_EDGE - 1;
        ball.velocity_y *= -bounceCoeff;
    }
    //====Physics

    mvaddch( previous_position_x, previous_position_y, BLANK );
	mvaddch( ball.position_x, ball.position_y, ball.symbol );
	move(LINES-1,COLS-1);
	refresh();

    previous_position_x = ball.position_x;
    previous_position_y = ball.position_y;
	
	signal( SIGALRM, ball_move);	/* for unreliable systems */
}

#pragma endregion Logics

#pragma region Main

void StartUpScreen() {
    system("clear");
    printf("WASD : Control velocity of ball\n");
    printf("q : Quit\n");
    printf("Press enter to start.\n");
    getchar();
}

void HandleInput() {
    char c;
	while ( (c = getchar()) != 'q' ){
        switch(c) {
            case 'a':
            ball.velocity_y += -0.2;
            break;
            case 'd':
            ball.velocity_y += 0.2;
            break;
            case 'w':
            ball.velocity_x += -0.2;
            break;
            case 's':
            ball.velocity_x += 0.2;
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

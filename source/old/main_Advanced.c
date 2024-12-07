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
#define BALLCOUNT 8

typedef struct ballObject {
    float position_y;
    float position_x;
    float velocity_y;
    float velocity_x;
    float radius;
	char	symbol ;
} ballObject;

ballObject balls[BALLCOUNT];
float bounceCoeff = 0.8;

#pragma endregion Declaration

#pragma region Logics

float Qsqrt(float x) {
    long i;
    float x2, y;
    const float threehalfs = 1.5f;

    x2 = x * 0.5f;
    y = x;
    i = *(long*)&y;
    i = 0x5f3759df - (i>>1);
    y = *(float*) &i;
    y = y * (threehalfs - (x2 * y * y));
    y = y * (threehalfs - (x2 * y * y));

    return y * 2;
}

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
    void ball_move(int);
    for(int i = 0; i < BALLCOUNT; i++) {
        ballObject* ball = balls + i;
        ball->position_y = BOT_ROW / 2;
	    ball->position_x = RIGHT_EDGE / 2;
	    ball->velocity_y = (float)(rand() % 100) / 100;
	    ball->velocity_x = (float)(rand() % 100) / 100;
        ball->radius = 1;
	    ball->symbol = 'a' + i;
    }
	initscr();
	noecho();
	crmode();

    mvaddch( balls[0].position_y, balls[0].position_x, balls[0].symbol );
    refresh();

	signal( SIGINT , SIG_IGN );

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

    static float previous_position_y[BALLCOUNT] = { 0 };
	static float previous_position_x[BALLCOUNT] = { 0 };
    //====Physics
    for(int i = 0; i < BALLCOUNT; i++) {
        ballObject* ball = balls + i;
        ball->position_y += ball->velocity_y;
        ball->position_x += ball->velocity_x;
        ball->velocity_y += 0.00981;

        if(ball->position_y < TOP_ROW) {
            ball->position_y = TOP_ROW + 1;
            ball->velocity_y *= -bounceCoeff;
        } else if (ball->position_y > BOT_ROW) {
            ball->position_y = BOT_ROW - 1;
            ball->velocity_y *= -bounceCoeff;
        }
        if(ball->position_x < LEFT_EDGE) {
            ball->position_x = LEFT_EDGE + 1;
            ball->velocity_x *= -bounceCoeff;
        } else if (ball->position_x > RIGHT_EDGE) {
            ball->position_x = RIGHT_EDGE - 1;
            ball->velocity_x *= -bounceCoeff;
        }

        for (int k = i + 1; k < BALLCOUNT; k++)
        {
            ballObject* ball2 = balls + k;
            float xdif = (ball->position_x - ball2->position_x);
            float ydif = (ball->position_y - ball2->position_y);
            float dist2= xdif * xdif + ydif * ydif;
            float dist = Qsqrt(xdif * xdif + ydif * ydif);
            float radSum = ball->radius + ball2->radius;
            if(dist2 < radSum * radSum) {
                float overlapDistance = radSum - dist;
                ball->position_x += xdif / dist * overlapDistance / 2;
                ball->position_y += ydif / dist * overlapDistance / 2;
                ball2->position_x += xdif / dist * -overlapDistance / 2;
                ball2->position_y += ydif / dist * -overlapDistance / 2;

                ball->velocity_x += xdif / dist * overlapDistance / 8;
                ball->velocity_y += ydif / dist * overlapDistance / 8;
                ball2->velocity_x += xdif / dist * -overlapDistance / 8;
                ball2->velocity_y += ydif / dist * -overlapDistance / 8;
            }
        }
        
        
        mvaddch( previous_position_y[i], previous_position_x[i], BLANK );
	    mvaddch( ball->position_y, ball->position_x, ball->symbol );

        previous_position_y[i] = ball->position_y;
        previous_position_x[i] = ball->position_x;
    }
    //====Physics
    move(BOT_ROW - 1, RIGHT_EDGE - 1);
    refresh();
	
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
            balls[0].velocity_x += -0.2;
            break;
            case 'd':
            balls[0].velocity_x += 0.2;
            break;
            case 'w':
            balls[0].velocity_y += -0.2;
            break;
            case 's':
            balls[0].velocity_y += 0.2;
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

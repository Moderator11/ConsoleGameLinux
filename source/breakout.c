#include "header.h"

void init_game(Ball *ball, Paddle *paddle, int bricks[BRICK_ROWS][WIDTH], int *score) {

    ball->x = WIDTH / 2;
    ball->y = HEIGHT / 2;
    ball->dx = 1;
    ball->dy = -1; // the ball starts going upwards

    paddle->x = WIDTH / 2 - PADDLE_WIDTH / 2;

    *score = 0;

    for (int i = 0; i < BRICK_ROWS; i++) {
        for(int j = 0 ; j < WIDTH ; j++) {
            bricks[i][j] = TRUE; // TRUE means brick exists; this generates the bricks
        }
    }

}

void draw_game(Ball *ball, Paddle *paddle, int bricks[BRICK_ROWS][WIDTH], int score) {

    clear();

    // Drawing the top wall
    for (int i = 0; i < WIDTH; i++) {
        mvaddch(0, i, '-');
    }


    // Drawing the bricks
    for (int i = 0; i < BRICK_ROWS; i++) {
        for(int j = 0 ; j < WIDTH ; j++) {
            if (bricks[i][j]) {
            mvaddch(i + 1, j, BRICK);
        }
        }
    }

    // Paddle
    for (int i = 0; i < PADDLE_WIDTH; i++) {
        /*
            mvprintw prints a string on the specified position
            (unlike mvaddch, which prints a character)
        */
        mvaddch(HEIGHT - 1, paddle->x + i, '='); 
    }

    // Ball
    mvaddch(ball->y, ball->x, 'O');

    // Score
    mvprintw(HEIGHT, 0, "Score: %d", score);

    refresh();

}

void update_game(Ball *ball, Paddle *paddle, int bricks[BRICK_ROWS][WIDTH], int *score, int *running) {
    
    // Move ball
    ball->x += ball->dx;
    ball->y += ball->dy;

    // Ball collisions with walls
    if (ball->x <= 0 || ball->x >= WIDTH - 1) {
        ball->dx *= -1;
    }
    if (ball->y <= 0) {
        ball->dy *= -1;
    }

    // Ball collisions with paddle
    if (ball->y == HEIGHT - 2 && ball->x >= paddle->x && ball->x < paddle->x + PADDLE_WIDTH) {
        ball->dy *= -1;
    }

    // Ball collision with bricks
    for (int row = 0; row < BRICK_ROWS; row++) {
        for (int col = 0; col < WIDTH; col++) {
            if (bricks[row][col] && ball->y == row + 1 && ball->x == col) {
                bricks[row][col] = FALSE; // Remove the brick
                ball->dy *= -1;
                (*score)++;
            }
        }
    }

    // When the ball falls below the paddle
    if (ball->y >= HEIGHT - 1) {
        *running = FALSE;
    }

}

void handle_input(Paddle *paddle) {

    int ch = getch();
    if (ch == KEY_LEFT && paddle->x > 0) {
        paddle->x--;
        paddle->x--;
    } else if (ch == KEY_RIGHT && paddle->x < WIDTH - PADDLE_WIDTH) {
        paddle->x++;
        paddle->x++;
    }
}

void start_game() {
    Ball ball;
    Paddle paddle;
    int bricks[BRICK_ROWS][WIDTH];
    int score;
    int running = TRUE;

    // Initializing curses
    initscr();
    cbreak();
    noecho();

    keypad(stdscr, TRUE); // to enable the keypad

    curs_set(0); // makes the cursor invisible

    timeout(0);

    init_game(&ball, &paddle, bricks, &score);

    while (running) {
        handle_input(&paddle);
        update_game(&ball, &paddle, bricks, &score, &running);
        draw_game(&ball, &paddle, bricks, score);
        usleep(BALL_SPEED);
    }

    // Game over
    clear();
    mvprintw(HEIGHT / 2, WIDTH / 2 - 5, "GAME OVER!");
    mvprintw(HEIGHT / 2 + 1, WIDTH / 2 - 5, "Score: %d", score);
    mvprintw(HEIGHT / 2 + 3, WIDTH / 2 - 5, "Press 'q' to quit");
    refresh();

    int ch;
    do {
        ch = getch();
    } while(ch != 'q');

    endwin();
    return;
}

/*
int main() {
    start_game();
    return 0;
}*/
#include "header.h"

int row;
int col;

int current_screen = 0;
int cmd = 0;

void banner1()
{   
    char s_1[] = "███████╗";
    char s_2[] = "██╔════╝";
    char s_3[] = "███████╗";
    char s_4[] = "╚════██║";
    char s_5[] = "███████║";
    char s_6[] = "╚══════╝";

    char i_1[] = "████████╗";
    char i_2[] = "╚══██╔══╝";
    char i_3[] = "██║";
    char i_4[] = "██║";
    char i_5[] = "████████╗";
    char i_6[] = "╚═══════╝";

    char t_1[] = "████████╗";
    char t_2[] = "╚══██╔══╝";
    char t_3[] = "██║";
    char t_4[] = "██║";
    char t_5[] = "██║";
    char t_6[] = "╚═╝";

    char e_1[] = "███████╗";
    char e_2[] = "██╔════╝";
    char e_3[] = "███████╗";
    char e_4[] = "██╔════╝";
    char e_5[] = "███████╗";
    char e_6[] = "╚══════╝";

    char r_1[] = "███████╗";
    char r_2[] = "██╔══██║";
    char r_3[] = "██████╔╝";
    char r_4[] = "██╔══██╗";
    char r_5[] = "██║  ██║";
    char r_6[] = "╚═╝  ╚═╝";

    // terminal size check
    int r_set = (row - 20) / 2;
    int c_set = (col - 64) / 2; 

    // sisters
    attron(COLOR_PAIR(1));
    mvprintw(r_set, c_set, "%s %s %s %s %s %s %s", s_1, i_1, s_1, t_1, e_1, r_1, s_1);
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    mvprintw(r_set + 1, c_set, "%s %s %s %s %s %s %s", s_2, i_2, s_2, t_2, e_2, r_2, s_2);
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(3));
    mvprintw(r_set + 2, c_set, "%s    %s    %s    %s    %s %s %s", s_3, i_3, s_3, t_3, e_3, r_3, s_3);
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(4));
    mvprintw(r_set + 3, c_set, "%s    %s    %s    %s    %s %s %s", s_4, i_4, s_4, t_4, e_4, r_4, s_4);
    attroff(COLOR_PAIR(4));

    attron(COLOR_PAIR(5));
    mvprintw(r_set + 4, c_set, "%s %s %s    %s    %s %s %s", s_5, i_5, s_5, t_5, e_5, r_5, s_5);
    attroff(COLOR_PAIR(5));

    attron(COLOR_PAIR(6));
    mvprintw(r_set + 5, c_set, "%s %s %s    %s    %s %s %s", s_6, i_6, s_6, t_6, e_6, r_6, s_6);
    attroff(COLOR_PAIR(6));

}

void banner2()
{
    char g_1[] = " ██████╗";
    char g_2[] = "██╔════╝";
    char g_3[] = "██║  ███╗";
    char g_4[] = "██║  ╚██║";
    char g_5[] = "╚██████╔╝";
    char g_6[] = "  ╚════╝";

    char a_1[] = "  █████╗";
    char a_2[] = "██╔══██╗";
    char a_3[] = "███████║";
    char a_4[] = "██╔══██║";
    char a_5[] = "██║  ██║";
    char a_6[] = "╚═╝  ╚═╝";

    char m_11[] = "██╗    ██╗";
    char m_12[] = "████╗████║";
    char m_13[] = "██╔███╔██║";
    char m_14[] = "██║╚══╝██║";
    char m_15[] = "██║    ██║";
    char m_16[] = "╚═╝    ╚═╝";

    char e_1[] = "███████╗";
    char e_2[] = "██╔════╝";
    char e_3[] = "███████╗";
    char e_4[] = "██╔════╝";
    char e_5[] = "███████╗";
    char e_6[] = "╚══════╝";

    // terminal size check
    int r_set = (row - 20) / 2;
    int c_set = (col - 38) / 2;

    // game
    attron(COLOR_PAIR(12));
    mvprintw(r_set + 7, c_set, "%s %s  %s %s", g_1, a_1, m_11, e_1);
    attroff(COLOR_PAIR(12));

    attron(COLOR_PAIR(11));
    mvprintw(r_set + 8, c_set, "%s  %s %s %s", g_2, a_2, m_12, e_2);
    attroff(COLOR_PAIR(11));

    attron(COLOR_PAIR(10));
    mvprintw(r_set + 9, c_set, "%s %s %s %s", g_3, a_3, m_13, e_3);
    attroff(COLOR_PAIR(10));

    attron(COLOR_PAIR(9));
    mvprintw(r_set + 10, c_set, "%s %s %s %s", g_4, a_4, m_14, e_4);
    attroff(COLOR_PAIR(9));

    attron(COLOR_PAIR(8));
    mvprintw(r_set + 11, c_set, "%s %s %s %s", g_5, a_5, m_15, e_5);
    attroff(COLOR_PAIR(8));

    attron(COLOR_PAIR(7));
    mvprintw(r_set + 12, c_set, "%s  %s %s %s", g_6, a_6, m_16, e_6);
    attroff(COLOR_PAIR(7));
}

void menu()
{
    // terminal size check
    int r_set = (row - 20) / 2;
    int c_set = (col - 38 + 18 - 4) / 2;

    mvprintw(r_set + 14, c_set - 14, "Press UP or DOWN to move menu and Press Enter to select");

    mvprintw(r_set + 16, c_set, "    play PingPong game    ");
    mvprintw(r_set + 17, c_set, "    play BreakOut game    ");
    mvprintw(r_set + 18, c_set, "       show Ranking       ");
    mvprintw(r_set + 19, c_set, "           exit           ");

    if (current_screen == 1)
    {
        attron(COLOR_PAIR(13));
        mvprintw(r_set + 16, c_set, ">>  play PingPong game  <<");
        attroff(COLOR_PAIR(13));
    }
    else if (current_screen == 2)
    {
        attron(COLOR_PAIR(13));
        mvprintw(r_set + 17, c_set, ">>  play BreakOut game  <<");
        attroff(COLOR_PAIR(13));
    }
    else if (current_screen == 3)
    {
        attron(COLOR_PAIR(13));
        mvprintw(r_set + 18, c_set + 3, ">>  show Ranking  <<");
        attroff(COLOR_PAIR(13));
    }
    else if (current_screen == 4)
    {
        attron(COLOR_PAIR(13));
        mvprintw(r_set + 19, c_set + 7, ">>  exit  <<");
        attroff(COLOR_PAIR(13));
    }

    refresh();
}

void pingpong_game()
{
    clear();

    char *title = "Ping Pong Game";
    char *cont1 = "Ping pong is a two-player game with paddles and a ball on a table.";
    char *cont2 = "Score points by landing the ball on the opponent's side.";
    char *cont3 = "Press b to go back to start screen";

    char *movement[] = {
        " Player 1",
        "  W - Move up",
        "  A - Move left",
        "  S - Move down",
        "  D - Move right",
        " Player 2",
        "  I - Move up",
        "  J - Move left",
        "  K - Move down",
        "  L - Move right",
    };

    char *rule[] = {
        " ", 
        "  q - Quit the game",
        "  Enter - start game"
    };

    int start = (col - START_POS -strlen(title)) / 2;
    int start1 = (col - START_POS - strlen(cont1)) / 2;
    int start2 = (col - START_POS - strlen(cont2)) / 2;
    int start3 = (col - START_POS - strlen(cont3)) / 2;

    int block_width = (col - 6) / 2;
    int block_length = row - 13;
    int left_start = 1;
    int right_start = START_POS + block_width + 3;

    int movement_count = sizeof(movement) / sizeof(movement[0]);
    int rule_count = sizeof(rule) / sizeof(rule[0]);

    int i;
    mvprintw(0, START_POS, "╔");
    for (i = 0; i < col - 4; i++)
        printw("═");
    printw("╗");

    mvprintw(1, START_POS, "║");
    mvprintw(1, START_POS + start, "%s", title);
    mvprintw(1, col - 2, "║");

    mvprintw(2, START_POS, "║");
    mvprintw(2, START_POS + start1, "%s", cont1);
    mvprintw(2, col - 2, "║");

    mvprintw(3, START_POS, "║");
    mvprintw(3, START_POS + start2, "%s", cont2);
    mvprintw(3, col - 2, "║");

    mvprintw(4, START_POS, "╚");
    for (i = 0; i < col - 4; i++)
        printw("═");
    printw("╝");

    mvprintw(6, left_start, "╔");
    for (i = 0; i < block_width; i++)
        printw("═");
    printw("╗");

    mvprintw(6, right_start, "╔");
    for (i = 0; i < block_width; i++)
        printw("═");
    printw("╗");

    mvprintw(7, left_start, "║");
    mvprintw(7, left_start + (block_width - 8) / 2, "Movement");
    mvprintw(7, left_start + block_width + 1, "║");

    mvprintw(7, right_start, "║");
    mvprintw(7, right_start + (block_width - 15) / 2, "General Command");
    mvprintw(7, right_start + block_width + 1, "║");
    
    for (i = 0; i < block_length; i++)
    {
        mvprintw(8 + i, left_start, "║");
        
        if (i < movement_count)
            mvprintw(8 + i, left_start + 2, "%s", movement[i]);
        
        mvprintw(8 + i, left_start + block_width + 1, "║");
    }

    for (i = 0; i < block_length; i++)
    {
        mvprintw(8 + i, right_start, "║");
        
        if (i < rule_count)
            mvprintw(8 + i, right_start + 2, "%s", rule[i]);
        
        mvprintw(8 + i, right_start + block_width + 1, "║");
    }

    mvprintw(row - 5, START_POS, "╚");
    for (i = 0; i < block_width; i++)
        printw("═");
    printw("╝");

    mvprintw(row - 5, right_start, "╚");
    for (i = 0; i < block_width; i++)
        printw("═");
    printw("╝");

    mvprintw(row - 3, START_POS, "╔");
    for (i = 0; i < col - 4; i++)
        printw("═");
    printw("╗");

    mvprintw(row - 2, START_POS, "║");
    mvprintw(row - 2, START_POS + start3, "%s", cont3);
    mvprintw(row - 2, col - 2, "║");

    mvprintw(row - 1, START_POS, "╚");
    for (i = 0; i < col - 4; i++)
        printw("═");
    printw("╝");
    
    refresh();

    while(1)
    {
        cmd = getch();
        if (cmd == 'b')
        {
            clear();
            return;
        }
        else if (cmd == '\n')
        {
	        Initialize();
            HandleInput();
	        CleanUp();

	        return;
        }

    }

    clear();
}

void breakout_game()
{
    clear();

    char *title = "Break Out Game";
    char *cont1 = "In Breakout, a paddle bounces a ball to break top bricks.";
    char *cont2 = "Players score by hitting bricks with the ball to make them disappear.";
    char *cont3 = "Press b to go back to start screen";

    char *movement[] = {
        " ",
        "  KEY_RIGHT - MOVE right",
        "  KEY_LEFT - MOVE Left"
    };

    char *rule[] = {
        " ", 
        "  q - Quit the game",
        "  Enter - start game"
    };

    int start = (col - START_POS -strlen(title)) / 2;
    int start1 = (col - START_POS - strlen(cont1)) / 2;
    int start2 = (col - START_POS - strlen(cont2)) / 2;
    int start3 = (col - START_POS - strlen(cont3)) / 2;

    int block_width = (col - 6) / 2;
    int block_length = row - 13;
    int left_start = 1;
    int right_start = START_POS + block_width + 3;

    int movement_count = sizeof(movement) / sizeof(movement[0]);
    int rule_count = sizeof(rule) / sizeof(rule[0]);

    int i;
    mvprintw(0, START_POS, "╔");
    for (i = 0; i < col - 4; i++)
        printw("═");
    printw("╗");

    mvprintw(1, START_POS, "║");
    mvprintw(1, START_POS + start, "%s", title);
    mvprintw(1, col - 2, "║");

    mvprintw(2, START_POS, "║");
    mvprintw(2, START_POS + start1, "%s", cont1);
    mvprintw(2, col - 2, "║");

    mvprintw(3, START_POS, "║");
    mvprintw(3, START_POS + start2, "%s", cont2);
    mvprintw(3, col - 2, "║");

    mvprintw(4, START_POS, "╚");
    for (i = 0; i < col - 4; i++)
        printw("═");
    printw("╝");

    mvprintw(6, left_start, "╔");
    for (i = 0; i < block_width; i++)
        printw("═");
    printw("╗");

    mvprintw(6, right_start, "╔");
    for (i = 0; i < block_width; i++)
        printw("═");
    printw("╗");

    mvprintw(7, left_start, "║");
    mvprintw(7, left_start + (block_width - 8) / 2, "Movement");
    mvprintw(7, left_start + block_width + 1, "║");

    mvprintw(7, right_start, "║");
    mvprintw(7, right_start + (block_width - 15) / 2, "General Command");
    mvprintw(7, right_start + block_width + 1, "║");
    
    for (i = 0; i < block_length; i++)
    {
        mvprintw(8 + i, left_start, "║");
        
        if (i < movement_count)
            mvprintw(8 + i, left_start + 2, "%s", movement[i]);
        
        mvprintw(8 + i, left_start + block_width + 1, "║");
    }

    for (i = 0; i < block_length; i++)
    {
        mvprintw(8 + i, right_start, "║");
        
        if (i < rule_count)
            mvprintw(8 + i, right_start + 2, "%s", rule[i]);
        
        mvprintw(8 + i, right_start + block_width + 1, "║");
    }

    mvprintw(row - 5, START_POS, "╚");
    for (i = 0; i < block_width; i++)
        printw("═");
    printw("╝");

    mvprintw(row - 5, right_start, "╚");
    for (i = 0; i < block_width; i++)
        printw("═");
    printw("╝");

    mvprintw(row - 3, START_POS, "╔");
    for (i = 0; i < col - 4; i++)
        printw("═");
    printw("╗");

    mvprintw(row - 2, START_POS, "║");
    mvprintw(row - 2, START_POS + start3, "%s", cont3);
    mvprintw(row - 2, col - 2, "║");

    mvprintw(row - 1, START_POS, "╚");
    for (i = 0; i < col - 4; i++)
        printw("═");
    printw("╝");
    
    refresh();

    while(1)
    {
        cmd = getch();
        if (cmd == 'b')
        {
            clear();
            return;
        }
        else if (cmd == '\n')
        {
            start_game();
            return;
        }
    }

    clear();
}

void show_ranking()
{
    clear();
    mvprintw(0, 0, "ranking");
    mvprintw(1, 0, "Press b to go back to start screen");
    refresh();

    while(1)
    {
        cmd = getch();
        if (cmd == 'b')
        {
            clear();
            return;
        }
    }

    clear();
}

void terminal_size()
{
    struct winsize wbuf;
    
    if (ioctl(0, TIOCGWINSZ, &wbuf) == -1)
    {
        perror("ioctl");
        exit(1);
    }
    else
    {
        row = wbuf.ws_row;
        col = wbuf.ws_col;
    }
}

void color_setting()
{
    start_color();
    use_default_colors();

    init_color(1, 941, 0, 1000);
    init_color(2, 949, 161, 1000);
    init_color(3, 957, 322, 1000);
    init_color(4, 966, 482, 1000);
    init_color(5, 971, 642, 1000);
    init_color(6, 988, 800, 1000);

    init_pair(1, 1, COLOR_BLACK);
    init_pair(2, 2, COLOR_BLACK);
    init_pair(3, 3, COLOR_BLACK);
    init_pair(4, 4, COLOR_BLACK);
    init_pair(5, 5, COLOR_BLACK);
    init_pair(6, 6, COLOR_BLACK);

    init_color(7, 86, 1000, 0);
    init_color(8, 195, 1000, 139);
    init_color(9, 304, 1000, 278);
    init_color(10, 412, 1000, 418);
    init_color(11, 521, 1000, 557);
    init_color(12, 629, 1000, 696);

    init_pair(7, 7, COLOR_BLACK);
    init_pair(8, 8, COLOR_BLACK);
    init_pair(9, 9, COLOR_BLACK);
    init_pair(10, 10, COLOR_BLACK);
    init_pair(11, 11, COLOR_BLACK);
    init_pair(12, 12, COLOR_BLACK);

    init_color(13, 1000, 1000, 1000);

    init_pair(13, COLOR_BLACK, 13);
}

void error_check(int command)
{
    if (command == KEY_UP)
    {
        if (current_screen == START_LIMIT)
            current_screen = current_screen;
        else
            current_screen = current_screen - 1;
    }
    else if (command == KEY_DOWN)
    {
        if (current_screen == END_LIMIT)
            current_screen = current_screen;
        else
            current_screen = current_screen + 1;
    }
}

int main(void)
{    
    setlocale(LC_ALL, "ko_KR.utf8");
    setlocale(LC_CTYPE, "ko_KR.utf8");

    terminal_size();

    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);

    color_setting();
    
    current_screen = 1;

    while(1)
    {
        banner1();
        banner2();
        menu();

        cmd = getch();

        if (cmd == '\n')
        {
            if (current_screen == 1)
            {
                pingpong_game();
                clear();
            }
            else if (current_screen == 2)
            {
                breakout_game();
                clear();
            }
            else if (current_screen == 3)
            {
                show_ranking();
                clear();
            }
            else if (current_screen == 4)
                break;
        }

        if (cmd == ERR)
            continue;
        
        switch (cmd)
        {
            case KEY_UP:
                error_check(cmd);
                break;

            case KEY_DOWN:
                error_check(cmd);
                break;
            
            default:
                break;
        }       
    }
    
    refresh();
    endwin();

    return 0;
}
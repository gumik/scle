#include <ncurses.h>
#include <set>
#include <cstring>
#include "board.h"
#include "opponent.h"
#include "scoreboard.h"

using namespace ScLe;
using namespace std;

multiset<char> msl;
char ct [8];

void getLetters (Board &board, Sack &sack, Opponent &opponent)
{
    int i = 0;
    while ((board.holder->amount () < 7) && (!sack.empty()))
    {
        char l = sack.takeOut ();
        board.holder->putIn (l);
        ct [i++] = l;
    }
    ct [i] = 0;
    board.holder->refresh ();

    if (i == 0)
        opponent.send ("EMPTY");
    else
        opponent.send (ct);
}

int editBoard (Board &board, Opponent &opponent)
{
    mvprintw (0, 0, "Uloz slowo.                    ");
    refresh ();

    int score = board.edit ();
    const char * affected_cells = board.affectedCells ();
    board.accept ();
    opponent.send (affected_cells);
    return score;
}

void receiveWord (Board &board, Opponent &opponent, ScoreBoard &scoreboard)
{
    mvprintw (0, 0, "Czekaj na ruch przeciwnika.    ");
    refresh ();

    const char * affected_cells = opponent.receive ();
    board.putWord (affected_cells);
    
    int score = board.calculateScore ();
    mvprintw (0, 0, "Zaakceptuj slowo za %d punktow. ", score);
    refresh ();
    
    getch ();
    board.accept ();
    opponent.send ("BOARD_ACCEPTED");
    scoreboard.addOpponent (score);
}

void receiveLetters (Board &board, Sack &sack, Opponent &opponent)
{
    const char * letters = opponent.receive ();

    if (strncmp (letters, "NONE", 4));
        for (int i = 0; i < strlen (letters); ++i)
            sack.takeOut (letters [i]);

    opponent.send ("LETTERS_TAKE_OUT");
}

int
main (int argc, char ** argv)
{
    Opponent opponent (argv [1], argv [2]);
    if (argc == 4)
        opponent.connect (true);
    else
        opponent.connect (false);

    initscr ();
    start_color ();
    noecho ();
    cbreak ();
    keypad (stdscr, true);
    refresh ();

    init_pair (1, COLOR_BLUE, COLOR_BLACK);
    init_pair (2, COLOR_RED, COLOR_BLACK);
    init_pair (3, COLOR_YELLOW, COLOR_BLACK);

    Board board (1, 2, 3, 2, 2);
    Sack sack;
    ScoreBoard score_board (5, 40);

    if (argc == 4)
    {
        getLetters (board, sack, opponent);
        opponent.receive ();

        /*receiveLetters (board, sack, opponent);
        printw ("odebralem literki\n");
        refresh ();*/

        for (int i = 0; i < 7; ++i)
            ct [i] = sack.takeOut ();
        ct [7] = 0;
    
        opponent.send (ct);
    }
    else
    {
        receiveLetters (board, sack, opponent);

        /*getLetters (board, sack, opponent);
        printw ("wylosowalem\n");
        refresh ();
        opponent.receive ();
        printw ("odebralem potwierdzenie\n");
        refresh ();*/

        const char * letters = opponent.receive ();
        for (int i = 0; i < 7; ++i)
        {
            board.holder->putIn (letters [i]);
            sack.takeOut (letters [i]);
        }
        board.holder->refresh ();

        receiveWord (board, opponent, score_board);
        receiveLetters (board, sack, opponent);
    }

    while ( true )
    {
        int score = editBoard (board, opponent);
        mvprintw (0, 0, "Czekaj na akceptacje slowa.");
        refresh ();
        opponent.receive ();
        score_board.addYour (score);
        getLetters (board, sack, opponent);
        opponent.receive ();

        receiveWord (board, opponent, score_board);
        receiveLetters (board, sack, opponent);
    }

    endwin();

    opponent.disconnect ();
}

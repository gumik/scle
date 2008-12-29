#include "scoreboard.h"

namespace ScLe
{

ScoreBoard::
ScoreBoard (int y, int x)
{
    win = newwin (2, 16, y, x);
    score_your = 0;
    score_oppo = 0;
    mvwprintw (win, 0, 0, "Ty:            0");
    mvwprintw (win, 1, 0, "Przeciwnik:    0");
    wrefresh (win);
}

ScoreBoard::
~ScoreBoard ()
{
    delwin (win);
}

void ScoreBoard::
addYour (int score)
{
    score_your += score;
    mvwprintw (win, 0, 12, "%4d", score_your);
    wrefresh (win);
}

void ScoreBoard::
addOpponent (int score)
{
    score_oppo += score;
    mvwprintw (win, 1, 12, "%4d", score_oppo);
    wrefresh (win);
}

}

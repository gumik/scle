#ifndef _SC_LE_SCOREBOARD_H_
#define _SC_LE_SCOREBOARD_H_

#include <ncurses.h>

namespace ScLe
{

// Wyswietla punktacje
class ScoreBoard
{
    public:
        ScoreBoard (int y, int x);
        ~ScoreBoard ();
        void addYour (int score);
        void addOpponent (int score);
        void clear ();

    private:
        WINDOW * win;
        int score_your;
        int score_oppo;
};

}

#endif /* _SC_LE_SCOREBOARD_H_ */

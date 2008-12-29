#ifndef _SC_LE_BOARD_H_
#define _SC_LE_BOARD_H_

#include <ncurses.h>
#include <set>
#include "point.h"
#include "holder.h"
#include "cstring"

namespace ScLe
{

class Board
{
    public:
        Board (int c_l, int c_w, int c_n, int begin_y = 0, int begin_x = 0);
        ~Board ();
        enum Direction { horizontal, vertical };
        int edit ();
        int putWord (const char * string);
        int calculateScore ();
        const char * affectedCells ();
        void accept ();
        void undo (bool lettersToHolder = true);
        Holder * holder;

    private:
        static const int SIZE = 15;
        static const int PREMIUM_L [SIZE][SIZE];
        static const int PREMIUM_W [SIZE][SIZE];
        char letters [SIZE][SIZE]; // literki na planszy
        int premium_l [SIZE][SIZE]; // premie literowe
        int premium_w [SIZE][SIZE]; // premie slowne
        const int color_premium_l, color_premium_w, color_new_l;
                                     // kolory pol z premiami
        std::set<Point> affected_cells;
            // pola na ktore cos polozono podczas edit ()
        WINDOW *win; // okno z plansza
        WINDOW *msgwin; // okno z wartoscia slowa

        bool putLetter (char letter, int y, int x);
        char eraseLetter (int y, int x);
        void printBlankCell (int y, int x);
        bool checkPosition ();
        int calculateWord (Point p, Direction d, bool single = false);
        void printScore ();
        char buffer[256];
};


}
#endif /* _SC_LE_BOARD_H_ */

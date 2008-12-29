#ifndef _SC_LE_MISC_H_
#define _SC_LE_MISC_H_

#include <ncurses.h>
#include <cstdlib>
#include <time.h>

namespace ScLe
{

// Zwraca wartość literki.
int letterPoints (char l);

// Zwraca string z literką "more human readable".
const char * humanLetter (char l);

// Drukuje "more human readable" literki
inline void lmvwprintw (WINDOW * win, int y, int x, char l)
{
    if (l < 97)
        mvwprintw (win, y, x, "%s", humanLetter (l));
    else
        mvwprintw (win, y, x, "%c", l);
}

inline void lwprintw (WINDOW * win, char l)
{
    if (l < 97)
        wprintw (win, "%s", humanLetter (l));
    else
        wprintw (win, "%c", l);
}

// Klasa do losowania literek (worek).
class Sack
{
    public:
        Sack ();
        char takeOut (char letter = 0);
        void putIn (char letter);
        void reset ();
        inline bool empty ();

    private:
        char contents[101];
        int amount;
        static const char letters [101];
};

inline bool Sack::
empty ()
{
    return amount == 0;
}

}

#endif /* _SC_LE_MISC_H_ */

#ifndef _SC_LE_HOLDER_H_
#define _SC_LE_HOLDER_H_

#include <ncurses.h>
#include <set>
#include "misc.h"

namespace ScLe
{

class Holder
{
    public:
        Holder (int y, int x);
        ~Holder ();
        bool putIn (char l);
        bool takeOut (char l);
        void putFromSack (Sack * sack);
        void clear ();
        void refresh ();
        int amount ();
        inline bool find (char l);

    private:
        std::multiset<char> letters;
        WINDOW * win;
        static const int capacity = 7;
};

inline bool Holder::
find (char l)
{
    return letters.find (l) != letters.end ();
}

}

#endif /* _SC_LE_HOLDER_H_ */

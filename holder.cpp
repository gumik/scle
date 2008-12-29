#include "holder.h"

namespace ScLe
{

Holder::
Holder (int y, int x)
{
    win = newwin (2, 21, y, x);
}

Holder::
~Holder ()
{
    delwin (win);
}

bool Holder::
putIn (char l)
{
    if (letters.size() == capacity)
        return false;
    
    letters.insert (l);
    return true;
}

bool Holder::
takeOut (char l)
{
    std::multiset<char>::iterator it = letters.find (l);
    if (it == letters.end ())
        return false;

    letters.erase (it);
    return true;
}

void Holder::
refresh ()
{
    werase (win);

    int x = 1;
    for (std::multiset<char>::iterator it = letters.begin ();
            it != letters.end (); ++it)
    {
        lmvwprintw (win, 0, x, *it);
        x += 3;
    }

    wmove (win, 1, 1);

    for (std::multiset<char>::iterator it = letters.begin ();
            it != letters.end (); ++it)
    {
        wprintw (win, "%d  ", letterPoints (*it));
    }

    wrefresh (win);
}

void Holder::
clear ()
{
    letters.clear ();
}

int Holder::
amount ()
{
    return letters.size ();
}

void Holder::
putFromSack (Sack * sack)
{
    while ((letters.size() < capacity) && (!sack->empty ()))
        letters.insert (sack->takeOut ());

    refresh ();
}

}

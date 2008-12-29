#include "board.h"

namespace ScLe
{

// Mapa premii literowych.
const int Board :: PREMIUM_L[SIZE][SIZE] = 
{
    1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1,
    1, 1, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1,
    2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 3, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 3, 1,
    1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1,
    1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1,
    1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1,
    1, 3, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 3, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2,
    1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 1, 1,
    1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1
};

// Mapa premii slownych.
const int Board :: PREMIUM_W[SIZE][SIZE] = 
{
    3, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 3,
    1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1,
    1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1,
    1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1,
    1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    3, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 3,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1,
    1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 
    1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1,
    1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1,
    3, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 3
};

Board:: 
Board (int c_l, int c_w, int c_n, int begin_y, int begin_x)
    : color_premium_l (c_l), color_premium_w (c_w), color_new_l (c_n)
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            letters [i][j] = 0;
            premium_l [i][j] = PREMIUM_L [i][j];
            premium_w [i][j] = PREMIUM_W [i][j];
        }
    }

    win = newwin (SIZE, 2*SIZE, begin_y, begin_x);
    keypad (win, true);

    msgwin = newwin (1, 4, begin_y + SIZE + 1, begin_x + 1);

    holder = new Holder (begin_y + SIZE + 1, begin_x + SIZE/2);
    
    for (int y = 0; y < SIZE; ++y)
    {
        for (int x = 0; x < SIZE; ++x)
            printBlankCell (y, x);
    }

    wrefresh (win);
}

/* Wchodzi w tryb edycji planszy.
   Zwraca liczbę - wartość ułożonego słowa.
   */
int Board::
edit ()
{
    int x = SIZE/2, y = SIZE/2;
    int key;
    affected_cells.clear ();

    do
    {
        key = mvwgetch (win, y, x*2);
    
        switch (key)
        {
            case KEY_UP:
                if (y > 0) --y;
                break;

            case KEY_DOWN:
                if (y < SIZE - 1) ++y;
                break;

            case KEY_LEFT:
                if (x > 0) --x;
                break;

            case KEY_RIGHT:
                if (x < SIZE - 1) ++x;
                break;

            case KEY_BACKSPACE:
                {
                    char letter = eraseLetter (y, x);
                    if (letter)
                    {
                        holder->putIn (letter);
                        holder->refresh ();

                        printScore ();
                    }
                }
                break;

            case 10:
                {
                    if (checkPosition ())
                    {
                        //mvprintw (0, 0, "%d   ", calculateScore ());
                        //refresh ();
                        return calculateScore ();
                    }
                    else
                    {
                        //mvprintw (0, 0, "zle!");
                        //refresh ();
                    }
                }
                break;

            default:
                if ((holder->find ((char)key)) && putLetter (char(key), y, x))
                {
                    holder->takeOut ((char)key);
                    holder->refresh ();

                    printScore ();
                }
        }
    }
    while (true);

}

void Board::
accept ()
{
    for (std::set<Point>::iterator it = affected_cells.begin ();
            it != affected_cells.end (); ++it)
    {
        premium_l [it->y][it->x] = premium_w [it->y][it->x] = 1;
        lmvwprintw (win, it->y, 2*it->x, letters [it->y][it->x]);
    }
    affected_cells.clear ();
    wrefresh (win);
}

void Board::
undo (bool lettersToHolder)
{
    for (std::set<Point>::iterator it = affected_cells.begin ();
            it != affected_cells.end (); ++it)
    {
        if (lettersToHolder)
            holder->putIn (letters [it->y][it->x]);
        letters [it->y][it->x] = 0;
        printBlankCell (it->y, it->x);
    }

    affected_cells.clear ();
    if (lettersToHolder)
        holder->refresh ();
    wrefresh (win);
}

int Board::
putWord (const char * string)
{
    /*for (int i = 0; i < strlen (word); ++i)
    {
        int xx = x, yy = y;
        if (dir == horizontal)
            xx += i;
        else
            yy += i;

        if (!letters [yy][xx])
            putLetter (word [i], yy, xx);
    }
    wrefresh (win);*/

    int i = 0;
    while (i < strlen (string))
    {
        int y = (int)(string [i++] - 48);
        int x = (int)(string [i++] - 48);
        char l = string [i++];

        putLetter (l, y, x);
    }

    wrefresh (win);
    return calculateScore ();
}

const char * Board::
affectedCells ()
{
    int i = 0;

    for (std::set<Point>::iterator it = affected_cells.begin ();
            it != affected_cells.end (); ++it)
    {
        buffer [i++] = (char)(it->y + 48);
        buffer [i++] = (char)(it->x + 48);
        buffer [i++] = letters [it->y][it->x];
    }

    buffer [i] = 0;

    return buffer;
}

bool Board::
putLetter (char letter, int y, int x)
{
    if (letters [y][x])
        return false;

    wattron (win, COLOR_PAIR (color_new_l));
    lmvwprintw (win, y, x*2, letter);
    wattroff (win, COLOR_PAIR (color_new_l));

    letters [y][x] = letter;
    affected_cells.insert (Point(y,x));

    return true;
}

char Board::
eraseLetter (int y, int x)
{
    if (affected_cells.find (Point (y, x)) == affected_cells.end ())
        return 0;

    char letter = letters [y][x];
    letters [y][x] = 0;
    affected_cells.erase (Point (y, x));
    printBlankCell (y, x);

    return letter;
}

void Board::
printBlankCell (int y, int x)
{
    char c;

    if (premium_l [y][x] > 1)
    {
        c = 183;
        wattrset (win, COLOR_PAIR (color_premium_l));
        if (premium_l [y][x] == 3)
            c = '+';
    }
    else if (premium_w [y][x] > 1)
    {
        c = 183;
        wattrset (win, COLOR_PAIR (color_premium_w));

        if (premium_w [y][x] == 3)
            c = '+';
    }
    else
        c = ' ';

    mvwprintw (win, y, 2*x, "%c ", c);
    wstandend (win);
}

int Board::
calculateScore ()
{
    Point s = *affected_cells.begin ();
    std::set<Point>::iterator it = affected_cells.end ();
    --it;
    Point t = *it;

    if (!(s == t))
    {
        int score = 0;
        Direction dir;

        if (s.x == t.x) // slowo pionowe
        {
            dir = horizontal;
            score += calculateWord (s, vertical);
        }
        else // slowo poziome
        {
            dir = vertical;
            score += calculateWord (s, horizontal);
        }

        for (std::set<Point>::iterator it = affected_cells.begin ();
                it != affected_cells.end (); ++it)
            score += calculateWord (*it, dir);

        /*if (holder->amount () == 0)
            score += 50;*/

        if (affected_cells.size () == 7)
            score += 50;

        return score;
    }
    else
        return calculateWord (s, horizontal) + calculateWord (s, vertical);
}

int Board::
calculateWord (Point p, Direction d, bool single)
{
    Point dir;
    if (d == horizontal)
        dir = Point (0, 1);
    else
        dir = Point (1, 0);

    Point s = p, t = p;

    while ((s.x >= 0) && (s.y >= 0) && (letters [s.y][s.x]))
        s -= dir;
    s += dir;

    while ((t.x < SIZE) && (t.y < SIZE) && (letters [t.y][t.x]))
        t += dir;
    t -= dir;

    if (!single && (s == t))
        return 0;

    int score = 0;
    int multiplier = 1;

    for (Point p = s; p <= t; p += dir)
    {
        score += letterPoints (letters [p.y][p.x]) * premium_l [p.y][p.x];
        multiplier *= premium_w [p.y][p.x];
    }
    score *= multiplier;

    return score;
}

/* Sprawdza, czy literki sa w jednej linii i czy ulozone sa przy juz
   ulozonych literkach (lub na polu startowym).
   Jesli dobrze, to zwraca true. */
bool Board::
checkPosition ()
{
    bool good_position = false;

    for (std::set<Point>::iterator it1 = affected_cells.begin ();
            it1 != affected_cells.end (); ++it1)
    {
        for (std::set<Point>::iterator it2 = affected_cells.begin ();
                it2 != affected_cells.end (); ++it2)
        {
            if ((it1->x != it2->x) && (it1->y != it2->y))
                return false;
        }
    }

    for (std::set<Point>::iterator it = affected_cells.begin ();
            it != affected_cells.end(); ++it)
    {
        if ((it->x > 0) && (letters [it->y][it->x - 1])
                && (affected_cells.find (Point (it->y, it->x - 1))
                    == affected_cells.end ()))
            good_position = true;

        if ((it->x < SIZE-1) && (letters[it->y][it->x + 1])
                && (affected_cells.find (Point (it->y, it->x + 1))
                    == affected_cells.end()))
            good_position = true;

        if ((it->y > 0) && (letters[it->y - 1][it->x])
                && (affected_cells.find (Point (it->y - 1, it->x))
                    == affected_cells.end()))
            good_position = true;

        if ((it->y < SIZE - 1) && (letters[it->y + 1][it->x])
                && (affected_cells.find(Point(it->y + 1, it->x))
                    == affected_cells.end()))
            good_position = true;
    }

    if (affected_cells.find (Point (7, 7)) != affected_cells.end ())
        good_position = true;

    if (!good_position)
        return false;

    std::set<Point>::iterator itt = affected_cells.end();
    Point last_point = *(--itt);
    Point first_point = *affected_cells.begin ();

    if (first_point.x == last_point.x) // slowo poziome
    {
        int x = first_point.x;

        for (int y = first_point.y; y <= last_point.y; ++y)
            if (!letters [y][x])
                return false;
    }
    else // slowo pionowe
    {
        int y = first_point.y;

        for (int x = first_point.x; x <= last_point.x; ++x)
            if (!letters [y][x])
                return false;
    }

    return true;
}

void Board::
printScore ()
{
    if (checkPosition ())
    {
        werase (msgwin);
        mvwprintw (msgwin, 0, 0, "%d", calculateScore ());
        wrefresh (msgwin);
    }
    else
    {
        werase (msgwin);
        mvwprintw (msgwin, 0, 0, "zle!");
        wrefresh (msgwin);
    }
}

Board::
~Board ()
{
    delwin (win);
    delwin (msgwin);
    delete holder;
}

}

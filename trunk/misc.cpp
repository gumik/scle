#include "misc.h"
#include <cstdio>

/*
0 punktów: blank (x2)
1 punkt: A (x9), E (x7), I (x8), N (x5), O (x6), R (x4), S (x4), W (x4), Z (x5)
2 punkty: C (x3), D (x3), K(x3), L(x3), M(x3), P (x3), T (x3), Y (x4)
3 punkty: B (x2), G(x2), H(x2), J (x2), Ł (x2), U (x2)
5 punktów: Ą (x1), Ę (x1), F (x1), Ó (x1), Ś (x1), Ż (x1)
6 punktów: Ć (x1)
7 punktów: Ń (x1)
9 punktów: Ź (x1)
*/

namespace ScLe
{

static const int letters_point [27] = {1, 3, 2, 2, 1, 5, 3, 3, 1, 3, 2, 2, 2,
    1, 1, 2, 0, 1, 1, 2, 3, 0, 1, 0, 2, 1};

int
letterPoints (char l)
{
    switch (l)
    {
        case 'E': return 5;
        case 'O': return 5;
        case 'A': return 5;
        case 'S': return 5;
        case 'L': return 3;
        case 'Z': return 5;
        case 'X': return 9;
        case 'C': return 6;
        case 'N': return 7;
        case ' ': return 0;
        default: return letters_point [(int)l - 97];
    }
}

const char *
humanLetter (char l)
{
    switch (l)
    {
        case 'E': return "e,";
        case 'O': return "o'";
        case 'A': return "a,";
        case 'S': return "s'";
        case 'L': return "l`";
        case 'Z': return "z.";
        case 'X': return "z'";
        case 'C': return "c'";
        case 'N': return "n'";
        case '_': return "_";
        default: return "!";
    }
}

/* class Sack */
const char Sack::letters[101] = {"__aaaaaaaaaeeeeeeeiiiiiiiinnnnnoooooorrrr"
                          "sssswwwwzzzzzcccdddkkklllmmmppptttyyyybbgghhjjLLuu"
                          "AEfOSZCNX"};

/*void Sack::
printSack ()
{
    move (0, 50);
    for (int i = 0; i < amount; ++i)
    {
        printw ("%c", contents [i]);
        if (i % 10 == 9)
            move (i / 10 + 1, 50);
    }
    printw (".");
    refresh ();
}*/

Sack::
Sack ()
{
    amount = 100;
    for (int i = 0; i < amount; ++i)
        contents[i] = letters[i];
    srand (time (NULL));
}

char Sack::
takeOut (char letter)
{
    if (amount == 0)
        return 0;

    int r;

    if (letter == 0) // losujemy
        r = rand () % amount;
    else // wybieramy konkretną (o ile jest)
    {
        r = 0;
        while ((contents [r] != letter) && (r < amount))
            ++r;

        if (r == amount)
            return 0;
    }

    char l = contents [r];
    contents [r] = contents [--amount];

    return l;
}


void Sack::
putIn (char letter)
{
    contents [amount++] = letter;
}

void Sack::
reset ()
{
    for (int i = 0; i < 100; ++i)
        contents[i] = letters[i];
    amount = 100;
}
/* end class Sack */

}

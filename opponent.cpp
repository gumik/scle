#include "opponent.h"

Opponent::
Opponent (const char * f_w, const char * f_r)
{
    srand (time (NULL));

    fifo_w_dest = new char [strlen (f_w) + 1];
    fifo_r_dest = new char [strlen (f_r) + 1];

    strcpy (fifo_w_dest, f_w);
    strcpy (fifo_r_dest, f_r);
}

void Opponent::
connect (bool first)
{
    printf ("Connecting...");
    fflush (stdout);

    if (first)
    {
        fifo_r = open (fifo_r_dest, O_RDONLY);
        fifo_w = open (fifo_w_dest, O_WRONLY);
    }
    else
    {
        fifo_w = open (fifo_w_dest, O_WRONLY);
        fifo_r = open (fifo_r_dest, O_RDONLY);
    }

    if ((fifo_w < 0) || (fifo_r < 0))
    {
        printf ("error!\n");
        close (fifo_w);
        close (fifo_r);
        return;
    }

    printf ("ok\nInitializing...");
    fflush (stdout);

    char buf [8], buf2 [8];

    write (fifo_w, "SCLEINIT", 8);
    read (fifo_r, buf, 8);

    if (strncmp ("SCLEINIT", buf, 8) != 0)
    {
        printf ("error!\n");
        close (fifo_r);
        close (fifo_w);
        return;
    }

    printf ("ok\n");

    /*sprintf (buf, "%8d", rand ());
    write (fifo_w, buf, 8);
    read (fifo_r, buf2, 8);

    int tmpi = strcmp (buf, buf2);

    if (tmpi == 0)
        printf ("error!\n");
    else if (tmpi > 0)
        printf ("ok (won).\n");
    else
    {
        printf ("ok (lose).\n");
    }

    return tmpi;*/
}

void Opponent::
send (const char * str)
{
    write (fifo_w, str, strlen (str) + 1);
}

char * Opponent::
receive ()
{
    read (fifo_r, buffer, 256);
    return buffer;
}

void Opponent::
disconnect ()
{
    close (fifo_w);
    close (fifo_r);
}

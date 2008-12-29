#ifndef _SC_LE_OPPONENT_H_
#define _SC_LE_OPPONENT_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>

/* Klasa do polaczenia sie z przeciwnikiem za pomoca potokow nazwanych
    Uwaga: potoki muszą mieć maskę dostępu równą 0777 */
class Opponent
{
    public:
        Opponent (const char * f_w, const char * f_r);
        void connect (bool first);
        void disconnect ();
        void send (const char * str);
        char * receive ();

    private:
        char * fifo_w_dest;
        char * fifo_r_dest;
        int fifo_w;
        int fifo_r;
        char buffer [256];
};

#endif /* _SC_LE_OPPONENT_H_ */

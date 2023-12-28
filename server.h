#ifndef __SERVER_H__
#define __SERVER_H__
#include "cell.h"

class Server: public Cell {
    int playerID;

    public:
        Server(int playerID);
        int getPlayer();
        char getChar() const override;
};

#endif

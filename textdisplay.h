#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
#include "observer.h"
#include "cell.h"
#include "tile.h"
#include "server.h"
#include "playerinfo.h"

using namespace std;

class Cell;

class TextDisplay: public Observer {
    vector<vector<char>> display;
    const int boardSize;
    int playerTurn;

    playerInfo p1;
    playerInfo p2;
    
    // gets the info of a link (data, virus, strength) depending on playerTurn
    string getLinkInfo(shared_ptr<Link> link) const;

    public:
        TextDisplay(int n);

        void notify(Cell &c) override;
        void notifyInfo(int abilityCount, int data, int viruses, vector<shared_ptr<Link>> links, int playerID) override;
        ~TextDisplay();
        void setPlayerTurn(int turn);
        friend ostream &operator<<(ostream &out, const TextDisplay &td);
};

#endif

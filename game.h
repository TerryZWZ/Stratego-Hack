#ifndef __GAME_H__
#define __GAME_H__
#include "game.h"
#include "board.h"
#include "player.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct Winner {
    bool win;
    int playerID;
};

class Game {
    bool graphics;
    Board board;
    Player p1;
    Player p2;
    int winCondition = 4;

    // utility function
    Player &getPlayer(int playerID);

    int playerTurn; // track which player's turn it is

    public:
        Game(bool graphics);
        void runGame();
        Winner checkWin();
        void addAbility(const string& player, const string& abilities);
        void abilityList(int player);
        void addLinks(int playerID, istream& in);
};

#endif

#ifndef __ABILITY_H__
#define __ABILITY_H__

#include "board.h"
#include "link.h"
#include <string>

using namespace std;

class Player;

class Ability {
    protected:
        int abilityID;
        int playerID;
        string name;
        Board* board;
        Player* player;
        bool used;

    public:
        Ability(int abilityID, int playerID, const string& name, Board* board, Player* player);
        virtual void ability(vector<shared_ptr<Link>> links, istream& in) = 0;
        string getName() const;
        bool usage() const; // returns used or not
        void abilityUsed();
        int getAbilityID() const;
        int getPlayerID() const;
};

#endif

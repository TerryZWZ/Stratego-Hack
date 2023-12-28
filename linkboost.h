#ifndef __LINKBOOST_H__
#define __LINKBOOST_H__
#include "ability.h"
#include "linkboostdecorator.h"
#include <iostream>

class Player;

class LinkBoost : public Ability {
    public:
        LinkBoost(int id, int playerID,  Board* board, Player* player);
        void ability(vector<shared_ptr<Link>> links, istream& in) override;
};

#endif

#ifndef __HACK_H__
#define __HACK_H__
#include "ability.h"
#include "firewalltile.h"
#include <iostream>
#include <limits>

class Hack: public Ability {
    public:
        Hack(int id, int playerID,  Board* board, Player* player);
        void ability(vector<shared_ptr<Link>> links, istream& in) override;
};

#endif

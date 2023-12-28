#ifndef __FIREWALL_H__
#define __FIREWALL_H__
#include "ability.h"
#include "firewalltile.h"
#include <iostream>
#include <limits>

class Firewall : public Ability {
    public:
        Firewall(int id, int playerID,  Board* board, Player* player);
        void ability(vector<shared_ptr<Link>> links, istream& in) override;
};

#endif

#ifndef __POLARIZE_H__
#define __POLARIZE_H__
#include "ability.h"
#include <iostream>

class Polarize : public Ability {
    public:
        Polarize(int id, int playerID,  Board* board, Player* player);
        void ability(vector<shared_ptr<Link>> links, istream& in) override;
};

#endif

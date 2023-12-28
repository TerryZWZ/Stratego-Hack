#ifndef __SCAN_H__
#define __SCAN_H__
#include "ability.h"
#include <iostream>

class Scan : public Ability {
    public:
        Scan(int id, int playerID,  Board* board, Player* player);
        void ability(vector<shared_ptr<Link>> links, istream& in) override;
};

#endif

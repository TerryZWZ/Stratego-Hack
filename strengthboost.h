#ifndef __STRENGTHBOOST_H__
#define __STRENGTHBOOST_H__
#include "ability.h"

class StrengthBoost: public Ability {
    public:
        StrengthBoost(int id, int playerID, Board *board, Player *player);
        void ability(vector<shared_ptr<Link>> links, istream& in) override;
};

#endif

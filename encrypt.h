#ifndef __ENCRYPT_H__
#define __ENCRYPT_H__
#include "ability.h"

class Encrypt: public Ability {
    public:
        Encrypt(int id, int playerID, Board* board, Player* player);
        void ability(vector<shared_ptr<Link>> links, istream& in) override;
};

#endif

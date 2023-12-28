#ifndef __DOWNLOAD_H__
#define __DOWNLOAD_H__
#include "ability.h"
#include <iostream>

class Download : public Ability {
    public:
        Download(int id, int playerID, Board* board, Player* player);
        void ability(vector<shared_ptr<Link>> links, istream& in) override;
};

#endif

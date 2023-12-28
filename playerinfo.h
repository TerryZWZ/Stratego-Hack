#ifndef __PLAYERINFO_H__
#define __PLAYERINFO_H__

#include <vector>
#include <memory>
#include "link.h"  // Include the header where Link is defined

using namespace std;

struct playerInfo {
    int playerID;
    int abilityCount;
    int data;
    int viruses;
    vector<shared_ptr<Link>> links;
};

#endif

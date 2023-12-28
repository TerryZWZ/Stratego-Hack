#ifndef __OBSERVER_H__
#define __OBSERVER_H__
#include "link.h"
#include <vector>
#include <memory>

using namespace std;

class Cell;

class Observer {
    public:
        virtual void notify(Cell &c) = 0;
        virtual void notifyInfo(int abilityCount, int data, int viruses, vector<shared_ptr<Link>> links, int playerID) = 0;
        virtual ~Observer() = default;
};

#endif

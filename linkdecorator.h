#ifndef __LINKDECORATOR_H__
#define __LINKDECORATOR_H__
#include "link.h"
#include <memory>

using namespace std;

class LinkDecorator : public Link{
    protected:
        shared_ptr<Link> component;

    public:
        LinkDecorator(shared_ptr<Link> component);
        shared_ptr<Link> getComponent() {return component;};
        virtual bool move(Direction d, int xlo, int xhi, int ylo, int yhi, int &xnew, int &ynew) = 0;
};

#endif

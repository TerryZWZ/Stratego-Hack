#ifndef _LINK_BOOST_DEC
#define _LINK_BOOST_DEC
#include "linkdecorator.h"

class LinkBoostDecorator : public LinkDecorator{
    public:
        LinkBoostDecorator(shared_ptr<Link> component);
        bool move(Direction d, int xlo, int xhi, int ylo, int yhi, int &xnew, int &ynew);
};

#endif

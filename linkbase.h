#ifndef __LINKBASE_H__
#define __LINKBASE_H__
#include "link.h"

class LinkBase : public Link{
public: 
    LinkBase(char _id, int _str, bool _data, int _pID, int r, int c);
    bool move(Direction d, int xlo, int xhi, int ylo, int yhi, int &xnew, int &ynew);
};

#endif

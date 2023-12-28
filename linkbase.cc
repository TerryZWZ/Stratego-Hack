#include "linkbase.h"

LinkBase::LinkBase(char _id, int _str, bool _data, int _pID, int r, int c): 
    Link(_id, _str, _data, _pID, r, c) {}

bool LinkBase::move(Direction d, int xlo, int xhi, int ylo, int yhi, int &xnew, int &ynew){
    if (d == Direction::Up) {
        if (getX() <= xlo ) return false;
        --xnew;
    }
    else if (d == Direction::Down) {
        if (getX() + 1 >= xhi) return false;
        ++xnew;
    }
    else if (d == Direction::Left) {
        if (getY() <= ylo) return false;
        --ynew;
    }
    else if (d == Direction::Right) {
        if (getY() + 1 >= yhi) return false;
        ++ynew;
    }
    return true;
}

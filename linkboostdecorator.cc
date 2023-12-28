#include "linkboostdecorator.h"

LinkBoostDecorator::LinkBoostDecorator(shared_ptr<Link> component) : LinkDecorator {component} {}

// moves the link twice
// as written, will fail if end point is out of bounds or on a friendly link
bool LinkBoostDecorator::move (Direction d, int xlo, int xhi, int ylo, int yhi, int &xnew, int &ynew){
    int xOriginal = xnew, yOriginal = ynew;
    getComponent()->setCoords(getX(), getY());
    if (!getComponent()->move(d, xlo, xhi, ylo, yhi, xnew, ynew)){
        return false;
    }
    getComponent()->setCoords(xnew, ynew);
    if (!getComponent()->move(d, xlo, xhi, ylo, yhi, xnew, ynew)){
        xnew = xOriginal;
        ynew = yOriginal;
        return false;
    }
    return true;
}

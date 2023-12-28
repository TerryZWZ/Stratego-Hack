#ifndef __TILE_H__
#define __TILE_H__
#include "cell.h"
#include "link.h"
#include <memory>

class Tile: public Cell {
    protected:
        bool isOccupied;
        shared_ptr<Link> link;

    public:
        Tile();
        char getChar() const override;
        virtual void occupyTile(shared_ptr<Link> link);
        bool occupied();
        virtual shared_ptr<Link> getLink() const;
        virtual void removeLink();
};

#endif

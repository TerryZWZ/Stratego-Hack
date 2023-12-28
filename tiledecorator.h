#ifndef __TILEDECORATOR_H__
#define __TILEDECORATOR_H__
#include "tile.h"

class TileDecorator: public Tile {
    protected:
        shared_ptr<Tile> component;
    
    public:
        TileDecorator(shared_ptr<Tile> component);
        void notifyObservers() override;
        void attach(shared_ptr<Observer> observer) override;
};

#endif

#ifndef __CELL_H__
#define __CELL_H__
#include "observer.h"
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Cell {
    int r, c;
    char symbol;
    bool walkable;
    bool server;

    protected:
        vector<shared_ptr<Observer>> observers;

    public:
        Cell(bool walkable, bool server);

        int getRow() const;
        int getCol() const;
        void setCoords(int r, int c);
        bool getState() const;
        bool isServer() const;
        virtual char getChar() const = 0;
        virtual void attach(shared_ptr<Observer> o);
        virtual void notifyObservers();
};

#endif

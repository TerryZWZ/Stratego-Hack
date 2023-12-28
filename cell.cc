#include "cell.h"

Cell::Cell(bool walkable, bool server): walkable{walkable}, server{server} {}

int Cell::getRow() const {
    return r;
}

int Cell::getCol() const {
    return c;
}

void Cell::setCoords(int r, int c) {
    this->r = r;
    this->c = c;
}

bool Cell::getState() const {
    return walkable;
}

bool Cell::isServer() const {
    return server;
}

void Cell::attach(shared_ptr<Observer> o) {
    if (o != nullptr) {
        observers.emplace_back(o);
    }
}

void Cell::notifyObservers() {
    for (auto observer : observers) {
        observer->notify(*this);
    }
}

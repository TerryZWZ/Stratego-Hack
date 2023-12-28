#include "tiledecorator.h"

TileDecorator::TileDecorator(shared_ptr<Tile> component) : component {component} {}

void TileDecorator::notifyObservers() {
    for (auto &observer : observers) {
        observer->notify(*this);
    }
}

void TileDecorator::attach(shared_ptr<Observer> observer) {
    observers.emplace_back(observer);
}

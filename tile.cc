#include "tile.h"

Tile::Tile() : Cell{true, false} {}

char Tile::getChar() const {
    if (link) {
        return link->getChar();
    }
    else {
        return '.';
    }
}

bool Tile::occupied() {
    if (link) {
        return true;
    }
    return false;
}

void Tile::occupyTile(shared_ptr<Link> link) {
    if (!occupied()) {
        this->link = link;
    }
}

shared_ptr<Link> Tile::getLink() const {
    return link;
}

void Tile::removeLink() {
    link = nullptr;
}

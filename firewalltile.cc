#include "firewalltile.h"
#include "player.h"

FirewallTile::FirewallTile(shared_ptr<Tile> component, int playerID, Player* player):
    TileDecorator{component}, isFirewallTile{true},  playerID{playerID}, player{player} {}

char FirewallTile::getChar() const {
    if (component->getLink()) {
        return component->getLink()->getChar();
    }
    else if (isFirewallTile) {
        return playerID == 1 ? 'm' : 'w';
    }
    else {
        return component->getChar();
    }
}

bool FirewallTile::getIsFirewallTile() const {
    return isFirewallTile;
}

void FirewallTile::occupyTile(shared_ptr<Link> link) {
    component->occupyTile(link);
    download(link);
}

void FirewallTile::download(shared_ptr<Link> link) {
    if (link && (link->getPlayerID() != playerID)) {
        link->reveal();

        if (!link->getIsData()) {
            player->opponent->download(*link);
            link->setDownloaded();
            player->opponent->removeLink(link->getChar());
        }
        if (link->getPlayerID() == component->getLink()->getPlayerID() && !link->getIsData()) {
            removeLink();
        }
        return;
    }
}

shared_ptr<Link> FirewallTile::getLink() const {
    return component->getLink();
}

void FirewallTile::removeLink() {
    component->removeLink();
}

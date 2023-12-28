#ifndef __FIREWALLTILE_H__
#define __FIREWALLTILE_H__
#include "tiledecorator.h"
#include <memory>

class Player;

class FirewallTile: public TileDecorator {
    bool isOccupied;
    bool isFirewallTile = false;
    int playerID;
    Player* player;

    public:
        FirewallTile(shared_ptr<Tile> component, int playerID, Player* player);
        char getChar() const override;
        bool getIsFirewallTile() const;
        void occupyTile(shared_ptr<Link> link) override;
        void download(shared_ptr<Link> link);
        shared_ptr<Link> getLink() const override;
        void removeLink() override;
};

#endif

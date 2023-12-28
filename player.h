#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "link.h"
#include "ability.h"
#include "linkboost.h"
#include "firewall.h"
#include "download.h"
#include "scan.h"
#include "polarize.h"
#include "strengthboost.h"
#include "encrypt.h"
#include "hack.h"
#include "board.h"
#include "textdisplay.h"
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Player {
    vector<shared_ptr<Link>> links;
    vector<shared_ptr<Ability>> abilities;
    Board* board;
    int viruses;
    int data;
    int id;
    vector<shared_ptr<Observer>> observers;

public:
    Player* opponent;
    
    // constructor taking a board
    Player(int _id, Board* b, string inp = "");

    // assigns opponent
    void setOpponent(Player* o);

    // attaches player to observer
    void attach(shared_ptr<Observer> o);  

    // notifies observer   
    void notifyObservers();

    // get links of the opponent player
    vector<shared_ptr<Link>> getOpponentLinks() const;

    // gets/sets link with id c
    int getLink(char c);
    bool moveLink(char c, int x, int y);
    bool moveLink(char c, Direction dir);
    void removeLink(char c);
    void setLink(char ch, shared_ptr<Link> link);
    
    // use/add abilities
    bool useAbility(int abilityID, istream& in);
    void addAbility(const char& ability, int id);
    void abilityList();
    int abilityCount();
    
    // adds link with parameters
    void addLink(char type, int strength, int col);

    // downloads link - does not delete it; should be cleaned up by caller
    void download(Link& l);

    int dataCount() const;
    int virusCount() const;
};

#endif

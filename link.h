#ifndef __LINK_H__
#define __LINK_H__
#include "direction.h"
#include <memory>

class Link {
    char linkID;                // the ID of the link (a-g, or A-G)
    int strength;               // the strength of the link
    bool isData;                // whether the link is Data (as opposed to Virus)
    int playerID;               // the player who controls the link (1, 2)
    int x, y;                   // coords of the link 
    bool hidden = true;         // whether the link is hidden from other player
    bool isEncrypted = false;   // whether the link is encrypted
    bool downloaded = false;    // whether the link is downloaded or not

    public:
        // constructor - takes strength, isData, playerID
        Link(char _id, int _str, bool _data, int _pID, int r, int c);
        Link();
        
        void setCoords(int _r, int _c);

        // move (Direction) : attempts to change values of x, y to move the link 
        // returns true if move is successful
        virtual bool move(Direction d, int xlo, int xhi, int ylo, int yhi, int &xnew, int &ynew) = 0;

        // misc getters for necessary fields
        bool getHidden() const;
        bool getIsEncrypted() const;
        void encrypt();
        void reveal();
        virtual char getChar() const;
        int getStrength() const;
        int getPlayerID() const;
        virtual int getX() const;
        virtual int getY() const;
        bool getIsData() const;
        void polarize();
        void strengthBoost();
        bool getDownloaded() const;
        void setDownloaded();

        // returns true if strength >= other.strength - should be called from the attacker
        bool operator> (Link &other);
};

#endif

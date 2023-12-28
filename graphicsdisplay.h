#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__
#include "window.h"
#include "observer.h"
#include "cell.h"
#include "tile.h"
#include "server.h"
#include "playerinfo.h"
#include <sstream>
#include <memory>

using namespace std;

class GraphicsDisplay : public Observer {
    Xwindow xw;
    vector<vector<char>> display;
    vector<vector<char>> linkTypes;
    int boardSize;
    int cellSize;
    playerInfo p1;
    playerInfo p2;
    int playerTurn;
    int gridStartY, gridEndY;

    public:
        GraphicsDisplay(int n);
        ~GraphicsDisplay() override = default;

        void setCell(int x, int y, char cellType, char linkType);
        void notify(Cell &c) override;
        void notifyInfo(int abilityCount, int data, int viruses, vector<shared_ptr<Link>> links, int playerID) override;
        void outputDisplay();
        void drawPlayerInfo(const playerInfo &pInfo, int yPos);
        string playerInfoToString(const playerInfo &pInfo);
        void setPlayerTurn(int turn);
        void drawLinkInfo(const vector<shared_ptr<Link>> &links, int yPos);
        string getLinkInfo(shared_ptr<Link> link) const;
        void drawString(int x, int y, const string &msg);
};

#endif

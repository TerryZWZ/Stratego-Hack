#include "graphicsdisplay.h"

GraphicsDisplay::GraphicsDisplay(int n): 
    xw{700, 700},
    boardSize{n},
    cellSize{350 / n},
    gridStartY{80},
    gridEndY{gridStartY+boardSize*cellSize} {
    vector<char> row;

    for (int i = 0; i < boardSize; ++i) {
        row.emplace_back('\0');
    }
    for (int i = 0 ; i < boardSize; ++i) {
        display.emplace_back(row);
        linkTypes.emplace_back(row);
    }
}

void GraphicsDisplay::setCell(int x, int y, char cellType, char linkType){
    int gridStartY = 80;
    
    int colour;
    
    if (cellType == 'S') { // server
        colour = Xwindow::Blue;
    }
    else if (cellType == 'm' || cellType == 'w') { // firewall
        colour = Xwindow::Orange;
    }
    else { // board tiles
        colour = Xwindow::Gray;
    }

    if (linkType == 'D') { // revealed data
        colour = Xwindow::Green;
    }
    else if (linkType == 'V') { // revealed virus
        colour = Xwindow::Red;
    }
    else if (linkType == 'U') { // hidden link
        colour = Xwindow::Black;
    }

    // Filling cell with colour
    xw.fillRectangle(y * cellSize, gridStartY + x * cellSize, cellSize, cellSize, colour);

    // Drawing a letter on non-tiles
    if (cellType != '.') {
        stringstream ss;
        ss << cellType;
        xw.drawString(y * cellSize + cellSize / 2, gridStartY + x * cellSize + cellSize / 2, ss.str(), Xwindow::Gray);
    }

    // Optimization
    xw.swapBuffers();
}

void GraphicsDisplay::notify(Cell &c) {
    int row = c.getRow();
    int col = c.getCol();

    if (c.getState()) {
        display[row][col] = c.getChar();

        // if it is a link
        if ((c.getChar() >= 'a' && c.getChar() <= 'h') || (c.getChar() >= 'A' && c.getChar() <= 'H')) {
            Tile& t = dynamic_cast<Tile&>(c);
            // not hidden and is a data
            if (!t.getLink()->getHidden() && t.getLink()->getIsData()) {
                linkTypes[row][col] = 'D';
                setCell(row, col, display[row][col], 'D');
            }
            // not hidden and is a virus
            else if (!t.getLink()->getHidden()) {
                linkTypes[row][col] = 'V';
                setCell(row, col, display[row][col], 'V');
            }
            // hidden link
            else {
                linkTypes[row][col] = 'U';
                setCell(row, col, display[row][col], 'U');
            }
        }
        else {
            linkTypes[row][col] = '\0';
            setCell(row, col, display[row][col], '\0');
        }
    }
}

void GraphicsDisplay::notifyInfo(int abilityCount, int data, int viruses, vector<shared_ptr<Link>> links, int playerID) {
    if (playerID == 1) {
        p1.playerID = playerID;
        p1.abilityCount = abilityCount;
        p1.data = data;
        p1.viruses = viruses;
        p1.links = links;
        drawPlayerInfo(p1, 10);
        drawLinkInfo(p1.links, gridStartY - 10);
    }
    else if (playerID == 2) {
        p2.playerID = playerID;
        p2.abilityCount = abilityCount;
        p2.data = data;
        p2.viruses = viruses;
        p2.links = links;
        drawPlayerInfo(p2, gridEndY + 20);
        drawLinkInfo(p2.links, gridEndY + gridStartY);
    }
    xw.swapBuffers();
}

void GraphicsDisplay::outputDisplay() {
    int playerInfoHeight = 60;
    int gridStartY = playerInfoHeight + 20;

    xw.fillRectangle(0, 0, 700, 700, Xwindow::Gray);

    // Player 1 Info
    drawPlayerInfo(p1, 10);
    drawLinkInfo(p1.links, gridStartY - 10);

    // Draw Grid
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            setCell(i, j, display[i][j], linkTypes[i][j]);
        }
    }

    int gridEndY = gridStartY + boardSize * cellSize;

    // Player 2 Info
    drawPlayerInfo(p2, gridEndY + 20);
    drawLinkInfo(p2.links, gridEndY + playerInfoHeight + 20); // Adjust position for link info

    // Optimization
    xw.swapBuffers();
}

void GraphicsDisplay::drawPlayerInfo(const playerInfo &pInfo, int yPos) {
    xw.fillRectangle(0, yPos - 10, 700, gridStartY, Xwindow::White);
    string info = playerInfoToString(pInfo);
    stringstream ss(info);
    string line;
    int lineNum = 0;
    while (getline(ss, line)) {
        xw.drawString(10, yPos + lineNum * 20, line, Xwindow::Black); // Adjust line spacing as needed
        lineNum++;
    }
}

string GraphicsDisplay::playerInfoToString(const playerInfo &pInfo) {
    stringstream ss;
    ss << "Player " << pInfo.playerID << ":" << endl;
    ss << "Downloaded: " << pInfo.data << "D, " << pInfo.viruses << "V" << endl;
    ss << "Abilities: " << pInfo.abilityCount;
    return ss.str();
}

void GraphicsDisplay::setPlayerTurn(int turn) {
    playerTurn = turn;
}

void GraphicsDisplay::drawLinkInfo(const vector<shared_ptr<Link>> &links, int yPos) {
    for (size_t i = 0; i < links.size(); ++i) {
        stringstream ss;
        ss << links[i]->getChar() << ": " << getLinkInfo(links[i]) << " ";
        xw.drawString(10 + i * 50, yPos, ss.str(), Xwindow::Black);
    }
}

string GraphicsDisplay::getLinkInfo(shared_ptr<Link> link) const {
    if (link->getHidden() && link->getPlayerID() != playerTurn) {
        return "? ";
    }
    else if (link->getIsData()) {
        return "D" + to_string(link->getStrength());
    }
    else {
        return "V" + to_string(link->getStrength());
    }
}

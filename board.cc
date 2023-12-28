#include "board.h"

Cell* Board::getCell(int r, int c) {
    if (r >= 0 && r < boardSize && c >= 0 && c < boardSize) {
        return &(*grid[r][c]);
    }
    else {
        return nullptr;
    }
}

vector<vector<shared_ptr<Cell>>> Board::getGrid() {
    return grid;
}

void Board::setCell(int r, int c, shared_ptr<Cell> cell) {
    grid[r][c] = cell;
    grid[r][c]->setCoords(r, c);
    grid[r][c]->attach(textDisplay);
    if (graphicsDisplay) {
        grid[r][c]->attach(graphicsDisplay);
    }
    grid[r][c]->notifyObservers();
}

void Board::init(shared_ptr<TextDisplay> td, shared_ptr<GraphicsDisplay> gd) {
    vector<shared_ptr<Cell>> row;

    textDisplay = td;
    graphicsDisplay = gd;
    
    // Map
    for (int i = 0; i < boardSize; ++i) {
        // col
        for (int j = 0; j < boardSize; ++j) {
            // servers at (r, c): (0, 3), (0, 4), (7, 3), (7, 4)
            if ((i == 0 || i == 7) && (j == 3 || j == 4)) {
                // player 1 servers
                if (i == 0) {
                    row.emplace_back(make_shared<Server>(1));
                }
                // player 2 servers
                else {
                    row.emplace_back(make_shared<Server>(2));
                }
            }
            else {
                row.emplace_back(make_shared<Tile>());
            }
        }
        grid.emplace_back(row);
        row.clear();
    }

    for (int r = 0; r < boardSize; r++) {
        for (int c = 0; c < boardSize; c++) {
            grid[r][c]->setCoords(r, c);
            grid[r][c]->attach(textDisplay);
            grid[r][c]->attach(graphicsDisplay);
        }
    }
}

void Board::update() {
    for (int r = 0; r < boardSize; r++) {
        for (int c = 0; c < boardSize; c++) {
            grid[r][c]->notifyObservers();
        }
    }
}

int Board::getSize() const {
    return boardSize;
}

shared_ptr<TextDisplay> Board::getTextDisplay() {
    return textDisplay;
}

shared_ptr<GraphicsDisplay> Board::getGraphicsDisplay() {
    return graphicsDisplay;
}

ostream& operator<<(ostream& out, const Board& board) {
    out << *board.textDisplay;
    return out;
}

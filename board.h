#ifndef __BOARD_H__
#define __BOARD_H__
#include "cell.h"
#include "tile.h"
#include "server.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include <vector>
#include <memory>

using namespace std;

class Board {
    vector<vector<shared_ptr<Cell>>> grid;          // the board 
    shared_ptr<TextDisplay> textDisplay;            // unique pointer to display of this board
    shared_ptr<GraphicsDisplay> graphicsDisplay;

    public:
        const int boardSize = 8;                    // constant representing board size
        // default constructor
        Board() = default;
        
        // returns pointer to cell at coords
        Cell* getCell(int r, int c);
        vector<vector<shared_ptr<Cell>>> getGrid();
        void setCell(int r, int c, shared_ptr<Cell> cell);

        // initializes board to RAIInet default
        void init(shared_ptr<TextDisplay> td, shared_ptr<GraphicsDisplay> gd);
        void update();

        int getSize() const;
        shared_ptr<TextDisplay> getTextDisplay(); // get the textDisplay
        shared_ptr<GraphicsDisplay> getGraphicsDisplay(); // get graphicsDisplay

        friend ostream& operator<<(ostream& out, const Board& board);
};

#endif

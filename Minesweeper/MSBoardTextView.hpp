#pragma once

#include "MinesweeperBoard.hpp"

class MSBoardTextView {
private:
    MinesweeperBoard& gameBoard;
public:
    MSBoardTextView(MinesweeperBoard& gameBoard);

    void display();
};
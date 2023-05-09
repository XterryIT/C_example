#pragma once

#include "MSBoardTextView.hpp"


class MSTextController {
private:
    MinesweeperBoard& gameBoard;
    MSBoardTextView view;
    int mines;
    void checkValue();
    int confirmAction();
    int number(string str);
public:
    MSTextController(MinesweeperBoard& gameBoard, const MSBoardTextView& view);

    void play();
};


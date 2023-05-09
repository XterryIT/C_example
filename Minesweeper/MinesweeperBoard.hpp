#pragma once

#include <vector>
#include <iostream>

using namespace std;


//implementujemy poziomy tudnosci naszej gry
enum class GameMode {
    DEBUG,
    EASY,
    NORMAL,
    HARD
};

//implementujemy tryby naszej gry
enum class GameState {
    RUNNING,
    FINISHED_WIN,
    FINISHED_LOSS
};


//Tryby naszych komrek
struct Field {
    bool hasMine = false;
    bool hasFlag = false;
    bool isRevealed = false;
};


//Tworzymy nasz bazowy klass
class MinesweeperBoard {
private:
    int width;
    int height;
    int mines;
    int revealedField;
    int winRevealedField;

    GameMode mode;
    GameState state;

    vector<vector<Field> > board;

    void randomMinePlacment();

public:
    
    MinesweeperBoard(int width, int height, GameMode mode, GameState state);

    void debug_display() const;
    
    int getBoardWidth() const;

    int getBoardHeight() const;

    int getMineCount() const;
    
    int countMines(int row, int col) const;

    bool hasFlag(int row, int col) const;

    void toggleFlag(int row, int col);

    void revealField(int row, int col);

    bool isRevealed(int row, int col) const;

    GameState getGameState() const;

    char getFieldInfo(int row, int col) const;
};

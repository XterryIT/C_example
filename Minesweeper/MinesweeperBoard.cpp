#include "MinesweeperBoard.hpp"
#include <ctime>
#include <iomanip>
#include <map>
#include <random>
#include <cmath>
#include <cstdlib>
#include <string>


using namespace std;



//tworzymy psewdo pole na którym randomowo umieściono miny 

vector<int> randomArray(int row, int col) {

    vector<int> arrayMinePos;
    int value = row;
    for (int i = 0; i < 2; i++, value = col) {
        random_device r;
        default_random_engine e1(r());
        uniform_int_distribution<int> uniform_dist(0, value - 1);
        int mean = uniform_dist(e1);
        //        cout << "Randomly-chosen mean: " << mean << '\n';
        arrayMinePos.push_back(mean);
    }

    return arrayMinePos;
}


// generujemy planszę o wymiarach height * weight z minami, ilość których zależy od moda
    // Easy - 10% pól gry z minami
    // Normal - 20% pól gry z minami
    // Hard - 30% pól gry z minami
    // DEBUG - wszystkie miny są dystrybówany z wyprzedzeniem

MinesweeperBoard::MinesweeperBoard(int width, int height, GameMode mode, GameState state) {
    this->width = width;
    this->height = height;
    this->revealedField = 0;
    this->mode = mode;
    this->state = state;


    for (int row = 0; row < height; row++) {
        this->board.push_back(vector<Field>());
        for (int col = 0; col < width; col++) {
            Field f;
            this->board[row].push_back(f);
        }
    }

    // EASY
    if (mode == GameMode::EASY) {
        this->mines = round(width * height * 10 / 100);
        this->winRevealedField = (this->width * this->height) - this->mines;
        randomMinePlacment();
    }

    // NORMAL
    if (mode == GameMode::NORMAL) {
        this->mines = round(width * height * 20 / 100);
        this->winRevealedField = (this->width * this->height) - this->mines;
        randomMinePlacment();
    }

    // HARD
    if (mode == GameMode::HARD) {
        this->mines = round(width * height * 30 / 100);
        this->winRevealedField = (this->width * this->height) - this->mines;
        randomMinePlacment();
    }

    // DEBUG
    if (mode == GameMode::DEBUG) {
        int minesCount = 0;
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                if (row == col) {
                    this->board[row][col].hasMine = true;
                }
                if (row == 0) {
                    this->board[row][col].hasMine = true;
                }
                if (col == 0 && row % 2 == 0) {
                    this->board[row][col].hasMine = true;
                }
                if (this->board[row][col].hasMine) {
                    minesCount++;
                }
            }
        }
        this->mines = minesCount;
        this->winRevealedField = (this->width * this->height) - this->mines;
    }
}


//rysuje pole dla debug moda(miny widoczne)

void MinesweeperBoard::debug_display() const {

    cout << "height:" << height;
    cout << "\tDEBUG MODE" << endl;
    cout << endl;

    for (int i = 0; i < this->width; i++) {
        cout << "    " << i;
        if (i == this->width - 1) {
            cout << endl;
        }
    }

    for (int row = 0; row < this->height; row++) {
        cout << row << " ";
        for (int col = 0; col < this->width; col++) {
            if (this->board[row][col].hasMine) {
                cout << "[M..]";
            }
            else if (this->board[row][col].isRevealed) {
                cout << "[.o.]";
            }
            else if (this->board[row][col].hasFlag) {
                cout << "[..f]";
            }
            else {
                cout << "[...]";
            }
        }
        cout << endl;
    }
}


//Nakłądania pola z randowomymi minami na nasze bazowe pole

void MinesweeperBoard::randomMinePlacment() {
    int minesCount = this->mines;
    while (minesCount > 0) {
        vector<int> randomArrayMinePos = randomArray(this->width, this->height);
        if (this->board[randomArrayMinePos[0]][randomArrayMinePos[1]].hasMine) {
            continue;
        }
        this->board[randomArrayMinePos[0]][randomArrayMinePos[1]].hasMine = true;
        minesCount--;
    }
}

// proste gettery - zwracają odpowiednie wartości

int MinesweeperBoard::getBoardWidth() const {
    return this->width;
}

int MinesweeperBoard::getBoardHeight() const {
    return this->height;
}

int MinesweeperBoard::getMineCount() const {
    return this->mines;
}

// liczymy miny wokół pola

int MinesweeperBoard::countMines(int row, int col) const {
    int mineCount = 0;

    // check
    if ((row >= this->height || row < 0) || (col >= this->width || col < 0) || !this->board[row][col].isRevealed) {
        return -1;
    }

    // top
    for (int i = col - 1; i < col + 2; i++) {
        if (row - 1 < 0 || (i < 0 || i >= this->width)) {
            continue;
        }
        else if (this->board[row - 1][i].hasMine) {
            mineCount++;
        }
    }

    // right
    for (int i = row; i < row + 2; i++) {
        if (i >= this->height || col + 1 >= this->width) {
            continue;
        }
        else if (this->board[i][col + 1].hasMine) {
            mineCount++;
        }
    }

    // bottom
    for (int i = col - 1; i < col + 1; i++) {
        if (row + 1 >= this->height || i < 0) {
            continue;
        }
        else if (this->board[row + 1][i].hasMine) {
            mineCount++;
        }
    }

    // left
    if (col - 1 >= 0 && this->board[row][col - 1].hasMine) {
        mineCount++;
    }

    return mineCount;
}

// zwrocają true, jeśli na pozycji zostało oznaczone flagą

bool MinesweeperBoard::hasFlag(int row, int col) const {
    if ((row > this->height || row < 0) || (col > this->width || col < 0) || !this->board[row][col].hasFlag ||
        this->board[row][col].isRevealed) {
        return false;
    }
    else {
        return true;
    }

}

// Ustawienia flagu na pole

void MinesweeperBoard::toggleFlag(int row, int col) {
    //Sprawdzamy żeby istnieła ta kmóra, nie była odkryta i nie przekrączała długość pola, i żeby stan gry był aktywny
    if (!((row > this->height || row < 0) || (col > this->width || col < 0) || this->board[row][col].isRevealed ||
        this->state != GameState::RUNNING)) {
        this->board[row][col].hasFlag ? this->board[row][col].hasFlag = false : this->board[row][col].hasFlag = true;
    }
}

// Odsłonięcie pola 

void MinesweeperBoard::revealField(int row, int col) {
    //Sprawdzamy żeby istnieła ta kmóra, nie była odkryta i nie przekrączała długość pola, i żeby stan gry był aktywny
    if (!((row >= this->height || row < 0) || (col >= this->width || col < 0) || this->board[row][col].hasFlag ||
        this->board[row][col].isRevealed ||
        this->state != GameState::RUNNING)) {

        // Jeśli pole nie zostało odkryte i niema na nim miny to odkrywamy go i kontynujemy grę 
        // W przeciwnym razie odrkywamy i kończymy grę 
        if (this->board[row][col].hasMine) {
            this->board[row][col].isRevealed = true;
            state = GameState::FINISHED_LOSS;
        }
        else {
            this->board[row][col].isRevealed = true;
            this->revealedField++;
            if (this->revealedField == this->winRevealedField) {
                state = GameState::FINISHED_WIN;
            }
        }
    }
}

//Zwrocamy true jesle pole odkryte

bool MinesweeperBoard::isRevealed(int row, int col) const {
    return this->board[row][col].isRevealed;
}


// zwrocamy aktualny stan gry:
GameState MinesweeperBoard::getGameState() const {
    return this->state;
}



// Zwracamy wszystkie informacje o polu
      // jeśli wiersz lub kolumna znajdują się poza tablicą - zwracamy #
      // jeśli pole nie jest odkryte i ma flagę - zwracamy F
      // jeśli pole nie jest odkryte i nie posiada flagi - zwracamy _
      // jeśli pole jest odkryte i ma moje - zwracamy x
      // jeśli pole jest odkryte i wokol niego nie ma min - zwracamy spacje 
      // jeśli pole jest odkryte i wokół są miny - zwracamy liczby

char MinesweeperBoard::getFieldInfo(int row, int col) const {
    if ((row > this->height || row < 0) || (col > this->width || col < 0)) {
        return '#';
    }
    else if (!this->board[row][col].isRevealed && this->board[row][col].hasFlag) {
        return 'F';
    }
    else if (!this->board[row][col].isRevealed && !this->board[row][col].hasFlag) {
        return '_';
    }
    else if (this->board[row][col].isRevealed && this->board[row][col].hasMine) {
        return 'x';
    }
    else if (this->board[row][col].isRevealed && (this->countMines(row, col) == 0)) {
        return ' ';
    }
    else {
        return this->countMines(row, col) + 48;
    }
}
#include "MSBoardTextView.hpp"
#include "MSTextController.hpp"

using namespace std;

//inicjalizujemy zminne gameBoard  naszym konstryktorze
MSBoardTextView::MSBoardTextView(MinesweeperBoard& gameBoard) : gameBoard(gameBoard) {
}

// rysujemy nasza gre
void MSBoardTextView::display() {
    int height = this->gameBoard.getBoardHeight();
    int width = this->gameBoard.getBoardWidth();
    char symbol;

    for (int i = 0; i < width; i++) {
        cout << "    " << i;
        if (i == width - 1) {
            cout << endl;
        }
    }

    for (int row = 0; row < height; row++) {
        cout << row << " ";
        for (int col = 0; col < width; col++) {
            symbol = this->gameBoard.getFieldInfo(row, col);
            switch (symbol) {
            case '#':
                break;
            case 'F':
                cout << "[..f]";
                break;
            case '_':
                cout << "[...]";
                break;
            case 'x':
                cout << "[.X.]";
                break;
            case ' ':
                cout << "[.o.]";
                break;
            default:
                cout << "[." << symbol << ".]";

            }

        }
        cout << endl;
    }
}
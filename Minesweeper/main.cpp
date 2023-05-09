#include <Windows.h>
#include "MinesweeperBoard.hpp"
#include "MSBoardTextView.hpp"
#include "MSTextController.hpp"


using namespace std;

//tutaj uruchomiamy nasz projekt minesweeper

int main(){
    
        setlocale(LC_ALL, "LC_ALL");

        GameMode mode = GameMode::HARD;
        GameState state = GameState::RUNNING;

        //tworzymy logike naszej gry(pole i reguly)
        MinesweeperBoard gameBoard(10, 10, mode, state);


        cout << endl << endl;

        //wyswietlamy nasze pole w konsoli
        MSBoardTextView view(gameBoard);

        gameBoard.debug_display();
        cout << endl;
        //urochomiamy nasz kontroller gry
        MSTextController ctrl(gameBoard, view);

        ctrl.play();
        return 0;
        
    
}

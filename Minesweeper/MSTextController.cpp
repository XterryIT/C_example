#include "MSTextController.hpp"
#include <locale>


using namespace std;



//inicjalizujemy zminne gameBoard i view w naszym konstryktorze
MSTextController::MSTextController(MinesweeperBoard& gameBoard, const MSBoardTextView& view) : gameBoard(gameBoard),
view(view) {
    this->mines = gameBoard.getMineCount();
}


//sprawdzamy wartości, potrzebnie wpisywać tylko liczby
void MSTextController::checkValue() {
    cin.clear(); // то возвращаем cin в 'обычный' режим работы
    cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
    cout << "Wprowadzono niepoprawna wartosc" << endl;
    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
}


// podtwierdzenie 
int MSTextController::confirmAction() {
    int confirm;
    cout << "Jestes pewien, ze chcesz otworzyc te komorke ?" << endl;
    cout << "Jesli tak to napisz dowolna liczbe, oprocz [0]. Jesli nie to napisz [0]" << endl;
    cout << "Twoj wybor: ";
    while (true) {
        cin >> confirm;
        if (cin.fail()) {
            checkValue();
        }
        else {
            break;
        }
    }
    return confirm;
}


//Sprawdza liczby którę my wpisujemy kiedy odkrywamy ko
int  MSTextController::number(string str) {
    int row;
    while (true) {
            cout << "Napisz numer " + str + ": ";
            cin >> row;
                if (cin.fail()) {
                    checkValue();
                }
                else {
                    break;
                }
    }
    return row;
}


void MSTextController::play() {
    int choose;
    int row;
    int col;
    int confirm;

    int height = this->gameBoard.getBoardHeight();
    int width = this->gameBoard.getBoardWidth();

    cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "\t\t\tMINESWEEPER" <<endl;
    cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << endl;

    this->view.display();

    cout << endl;
    cout << "-------------" << endl;
    cout << "Mines: " << this->mines << endl;
    cout << "-------------" << endl << endl;

    do {
        cout << "-------------------------------------------------------------" << endl;
        while (true) {
            cout << "Jezeli chcesz otworzyc polie napisz [1]" << endl;
            cout << "Jezeli chcesz umiescic flage na pole, napisz [2]" << endl;
            cout << "Twoj wybor: ";
            cin >> choose;
            if (cin.fail()) {
                checkValue();
            }
            else {
                break;
            }
        }
        cout << "-------------------------------------------------------------" << endl;

        switch (choose) {
        case 1:
            confirm = confirmAction();
            if (confirm == 0) {
                break;
            }

            cout << "Napisz wspolrzedne komorki, ktora chcesz otworzyc." << endl;
            row = number("rzedu");
            col = number("kolumny");

            if (row < height || col < width) {
                this->gameBoard.revealField(row, col);
            }
            else
            {
                cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
                cout << "Liczby przekroczaja dlugosc pola" << endl;
                cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
                break;
            }
            cout << endl;

            break;
        case 2:
            confirm = confirmAction();
            if (confirm == 0) {
                break;
            }

            cout << "Napisz wspolrzedne komorki, na ktora chcesz umiescic flage." << endl;
            row = number("rzedu");
            col = number("kolumny");
            cout << endl;

            if (row < height || col < width) {
                this->gameBoard.toggleFlag(row, col);
                if (this->gameBoard.hasFlag(row, col)) {
                    this->mines--;
                    if (this->mines < 0) {
                        this->gameBoard.toggleFlag(row, col);
                        this->mines++;

                        cout << endl << endl;
                        cout << "<><><><><><><><><><><><><><><><><><><><><><><><><><>" << endl;
                        cout << "To jest maksymalna ilosc mozliwych flag!" << endl;
                        cout << "Jesli uwazasz, ze zle umiesciles flage, usun nadmair." << endl;
                        cout << "<><><><><><><><><><><><><><><><><><><><><><><><><><>" << endl;
                    }
                }
                else {
                    this->mines++;
                }
            }
            else
            {
                cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
                cout << "Liczby przekroczaja dlugosc pola" << endl;
                cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
                break;
            }
           
            break;
        default:
            cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
            cout << "Nie ma podobnej opcji, sprobuj ponownie!" << endl;
            cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
        }
        this->view.display();

        cout << endl;
        cout << "-----------" << endl;

        cout << "Mines: " << this->mines << endl;

        cout << "-----------" << endl << endl;

    } while (this->gameBoard.getGameState() == GameState::RUNNING);

    this->gameBoard.debug_display();
    if (this->gameBoard.getGameState() == GameState::FINISHED_WIN) {
        cout << endl << endl;
        cout << "************************************" << endl;
        cout << "Gratulacja! Wygrales!" << endl;
        cout << "Wszystkie miny zostaly rozminowany!" << endl;
        cout << "************************************" << endl;
    }
    else {
        cout << endl << endl;
        cout << "************************************" << endl;
        cout << "Boom! Boom! Boom!" << endl;
        cout << "Urwalo ci rece i nogi i bolesnie zginal !" << endl;
        cout << "Sprobuj ponownie, moze nastepnym razem ci uda sie rozminowac (@_@)" << endl;
        cout << "************************************" << endl;
    }
}
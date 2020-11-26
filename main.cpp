
#include <stdlib.h>
#include <time.h>

#include "TicTacToe.h"

int main(int argc, char *argv[]) {

    srand(time(NULL));

    TicTacToe game;

    int playerWon = 0, aiWon = 0, noWon = 0;
    int counter = 0;
    int end = 10;

    if(rand() % 2 == 0)
        game.nextAIMove(false);
    
    while(counter < end) {

        game.performMoves();

        int won = game.hasWon();
        if(won != -2) {
            switch(won) {
                case 1:
                    ++playerWon;
                    break;
                case 2:
                    ++noWon;
                    break;
                case 3:
                    ++aiWon;
                    break;
            }

            game.resetField();
            game.setGameStatus(true);
            ++counter;
        }
    }

    std::cout << "Player: " << playerWon << "\nAI: " << aiWon << "\nNo: " << noWon << std::endl;

    return 0;
}

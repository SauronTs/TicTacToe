
#include <stdlib.h>
#include <time.h>

#include "TicTacToe.h"

int main(int argc, char *argv[]) {

    srand(time(NULL));

    TicTacToe game;

    if(rand() % 2 == 0)
        game.nextAIMove();

    game.printField();
    
    char input = ' ';

    while(input != 'q' && game.isGameRunning()) {
        std::cin >> input;

        game.getInput(input);
        game.printField();
    }

    std::cout << std::endl;

    return 0;
}

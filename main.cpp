#include <iostream>
#include <array>
#include <map>
#include <algorithm>
#include <limits>
#include <stdlib.h>
#include <time.h>

class TicTacToe {
public:
    TicTacToe();

    void printField();
    void setPosition(int x, int y, bool isPlayer);
    void getInput(char input);
    void nextAIMove();

    bool isGameRunning() const {return m_gameIsRunning;}

private:
    std::array<std::array<char, 3>, 3> m_field;
    bool m_gameIsRunning = true;

    bool isPositionBlocked(int x, int y) const;
    bool nextPlayerMove(int number);
    bool isNumber(char input) const;
    int hasWon();
    bool isFull() const;
    void deletePosition(int x, int y);
    int minimax(int depth, bool isMax);

    std::map<char, int> m_scores = {{'X', -1}, {'O', 1}};

    const static char EMPTY = '#';
    const static char PLAYER = 'X';
    const static char AI = 'O';
};

void TicTacToe::deletePosition(int x, int y) {
    m_field[x][y] = EMPTY;
}

bool TicTacToe::isFull() const {
    for(auto i : m_field)
        for(auto a : i)
            if(a == EMPTY)
                return false;

    return true;
}

int TicTacToe::hasWon() {
    for(int i = 0; i < 3; ++i) {
        if(m_field[i][0] == m_field[i][1] && m_field[i][1] == m_field[i][2] && (m_field[i][0] != EMPTY)) {
            return m_scores[m_field[i][0]];
        }
        if(m_field[0][i] == m_field[1][i] && m_field[1][i] == m_field[2][i] && (m_field[0][i] != EMPTY)) {
            return m_scores[m_field[0][i]];
        }
    }

    if((m_field[0][0] == m_field[1][1] && m_field[1][1] == m_field[2][2]) || (m_field[0][2] == m_field[1][1] && m_field[1][1] == m_field[2][0]))
        if(m_field[1][1] != EMPTY)
            return m_scores[m_field[1][1]];

    if(isFull())
        return 0;

    return -2;
}

bool TicTacToe::isNumber(char input) const {
    return input >= '1' && input <= '9';
}

void TicTacToe::getInput(char input) {
    if(!isNumber(input)) {
       return;
    }

    if(nextPlayerMove(input - '0')) {
        nextAIMove();
    }

    if(hasWon() == 0)
        m_gameIsRunning = false;
}

bool TicTacToe::nextPlayerMove(int number) {
    int x = (number - 1) / 3;
    int y = (number - 1) - (number - 1) / 3 * 3;

    if(!isPositionBlocked(x, y)) {
        setPosition(x, y, true);

        if(hasWon() == -1) {
            m_gameIsRunning = false;
            return false;
        }

        return true;
    }else {
        std::cerr << "Illegal player move" << std::endl;
        return false;
    }

    if(hasWon() != -2) {
        m_gameIsRunning = false;
        return false;
    }

    return true;
}

void TicTacToe::nextAIMove() {
    int bestScore = std::numeric_limits<int>::min();
    int bestX = 0, bestY = 0;

    for(int i = 0; i  < 3; ++i) {
        for(int a = 0; a < 3; ++a) {
            if(!isPositionBlocked(i, a)) {
                setPosition(i, a, false);
                int score = minimax(0, false);
                deletePosition(i, a);
                if(score > bestScore) {
                    bestScore = score;
                    bestX = i;
                    bestY = a;
                }
            }
        }
    }

    setPosition(bestX, bestY, false);

    if(hasWon() == 1)
        m_gameIsRunning = false;
}

int TicTacToe::minimax(int depth, bool isMax) {
    int bestScore = std::numeric_limits<int>::min();

    if(hasWon() != -2) {
        return hasWon();
    }

    if(!isMax)
        bestScore = std::numeric_limits<int>::max();

    for(int i = 0; i < 3; ++i) {
        for(int a = 0; a < 3; ++a) {
            if(!isPositionBlocked(i, a)) {
                setPosition(i, a, !isMax);
                int score = minimax(depth + 1, !isMax);
                deletePosition(i, a);

                if(isMax) {
                    bestScore = std::max(bestScore, score);
                }else {
                    bestScore = std::min(bestScore, score);
                }
            }
        }
    }

    return bestScore;
}

bool TicTacToe::isPositionBlocked(int x, int y) const {
    return m_field[x][y] != EMPTY;
}

void TicTacToe::setPosition(int x, int y, bool isPlayer) {
    char character = AI;

    if(isPlayer)
        character = PLAYER;
    
    m_field[x][y] = character;
}

TicTacToe::TicTacToe() {
    for(int i = 0; i < 3; ++i) {
        for(int a = 0; a < 3; ++a) {
            m_field[i][a] = EMPTY;
        }
    }
}

void TicTacToe::printField() {
    std::cout << "----------------------------------" << std::endl;

    for(auto i : m_field) {
        for(auto a : i) {
            std::cout << a << " ";
        }
        std::cout << std::endl;
    }

    if(m_gameIsRunning) {
        std::cout << std::endl << "Input: ";
    }else {
        if(hasWon() == -1) {
            std::cout << std::endl << "Player has won";
        }else if(hasWon() == 1) {
            std::cout << std::endl << "AI has won";
        }else {
            std::cout << std::endl << "No one has won";
        }
    }
}

int main(int argc, char *argv[]) {

    srand(time(NULL));

    TicTacToe game;

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
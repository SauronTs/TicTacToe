#include "TicTacToe.h"

#include <memory>
#include <vector>

struct Position {
    int x;
    int y;
    Position(int x, int y) : x(x), y(y) {}
};

TicTacToe::TicTacToe() {
    for(int i = 0; i < 3; ++i) {
        for(int a = 0; a < 3; ++a) {
            m_field[i][a] = EMPTY;
        }
    }
}

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
        return 2;

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

    if(hasWon() == 2)
        m_gameIsRunning = false;
}

bool TicTacToe::nextPlayerMove(int number) {
    int x = (number - 1) / 3;
    int y = (number - 1) - (number - 1) / 3 * 3;

    if(!isPositionBlocked(x, y)) {
        setPosition(x, y, true);
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
    int bestScore = 1;
    std::map<std::unique_ptr<Position>, int> moves;
    std::vector<Position*> bestMoves;

    for(int i = 0; i  < 3; ++i) {
        for(int a = 0; a < 3; ++a) {
            if(!isPositionBlocked(i, a)) {
                setPosition(i, a, false);
                int score = minimax(0, false);
                deletePosition(i, a);
                moves.insert(std::make_pair(new Position(i, a), score));
                if(score > bestScore)
                    bestScore = score;
            }
        }
    }   

    for(auto & [key, value] : moves) {
        if(value == bestScore)
            bestMoves.push_back(key.get());
    }

    Position *random = bestMoves[rand() % bestMoves.size()];

    setPosition(random->x, random->y, false);

    if(hasWon() != -2)
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
        if(hasWon() == 1) {
            std::cout << std::endl << "Player has won";
        }else if(hasWon() == 3) {
            std::cout << std::endl << "AI has won";
        }else {
            std::cout << std::endl << "No one has won";
        }
    }
}
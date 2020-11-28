#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <iostream>
#include <array>
#include <map>
#include <algorithm>
#include <limits>

class TicTacToe {
public:
    TicTacToe();

    void printField();
    void performMoves();
    bool nextAIMove(bool firstAi);
    int hasWon();
    void resetField();
    static bool isNumber(char input);

    bool isGameRunning() const {return m_gameIsRunning;}
    void setGameStatus(bool status);

private:
    std::array<std::array<char, 3>, 3> m_field;
    bool m_gameIsRunning = true;

    void setPosition(int x, int y, bool isPlayer);
    bool isPositionBlocked(int x, int y) const;
    bool isFull() const;
    void deletePosition(int x, int y);
    int minimax(int depth, bool isMax);

    std::map<char, int> m_scores = {{'X', 1}, {'O', 3}};

    const static char EMPTY = '#';
    const static char PLAYER = 'X';
    const static char AI = 'O';
};

#endif // TICTACTOE_H
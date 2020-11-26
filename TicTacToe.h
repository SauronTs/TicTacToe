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

    std::map<char, int> m_scores = {{'X', 1}, {'O', 3}};

    const static char EMPTY = '#';
    const static char PLAYER = 'X';
    const static char AI = 'O';
};

#endif // TICTACTOE_H
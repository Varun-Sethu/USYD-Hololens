//
// Created by varun on 26/11/2018.
//

#ifndef TICTACTOE_BOARD_H
#define TICTACTOE_BOARD_H

#include <array>
#include <string>
#include <map>
#include <vector>
#include <iterator>
#include <algorithm>
#include <utility>

#define HOLDER std::array<std::array<Board::States, 3>, 3>


// Board class which contains the data strucutre which holds the state of the game
class Board {
public:
    // UTILITY FUNCTIONS and stuff
    static enum States {
        X,
        O,
        NULL__,
        W,
        L
    };
    std::map<States, const char*> stateMap;
    static States inverse(States state);


    // CONSTRUCTORS
    Board(const Board& board);
    Board(const Board&& board) noexcept;
    // A lot of redundancy here
    Board();

    // Getters & Setters
    HOLDER& getBoard() const;
    std::array<std::array<std::string, 3>, 3> exportAsString() const;
    std::vector<std::pair<int, int>> getEmptySquares() const;
    std::vector<std::string> getBoardVectorDump() const;
    bool updateBoard(std::pair<int, int> coords, Board::States value);
    int getValue(Board::States reference) const;
    int operator-(const Board& rhs, const Board& lhs, Board::States player);


private:
    HOLDER __boardConfig = {std::array<Board::States, 3>{NULL__, NULL__, NULL__},
                            std::array<Board::States, 3>{NULL__, NULL__, NULL__},
                            std::array<Board::States, 3>{NULL__, NULL__, NULL__}};

    // Iterator method that takes a function pointer and iterates over the whole board
    void __applyToBoard(void (*foo)(unsigned long, unsigned long, std::array<States, 3>*, States*)) const;
    void initMoves();
    // Compute the number of potential ways the player could win the game given a refrence board
    // Dammit, its unreadable
    std::vector<std::vector<std::vector<std::vector<Board::States>>>> __winningMoves;

};



#endif //TICTACTOE_BOARD_H

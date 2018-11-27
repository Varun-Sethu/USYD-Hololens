//
// Created by varun on 26/11/2018.
//

#include "../includes/Board.h"

#define HOLDER std::array<std::array<Board::States, 3>, 3>






// CONSTRUCTORS
Board::Board() {
    stateMap.insert(std::pair<Board::States, const char*>(X, "X"));
    stateMap.insert(std::pair<Board::States, const char*>(O, "O"));
    stateMap.insert(std::pair<Board::States, const char*>(NULL__, " "));
    this->initMoves();
}
Board::Board(const Board &board) {
    this->__boardConfig = board.getBoard();
}
Board::Board(const Board &&board) noexcept {
    this->__boardConfig = board.getBoard();
}

// Privy functions
void Board::__applyToBoard(void (*foo)(unsigned long, unsigned long, std::array<States, 3>*, States*)) const {
    auto& cop = this->__boardConfig;

    for(auto it = cop.begin(); it != cop.end(); ++it) {
        for (auto itj = it->begin(); it->end(); ++itj) {
            foo(cop.begin() - it, it->begin() - itj, it, itj);
        }
    }

}


// Operators
int Board::operator-(const Board &rhs, const Board &lhs, const Board::States ref) {
    const Board &boardCop = rhs;
    // Configure the board we want to subtract from first, this board must be configured to replace all W's with the player's token
    int singleInst = 0;
    for (auto& c: boardCop.getBoard()) {
        std::replace(c.begin(), c.end(), W, ref);
        // determine how many instances have occurred
        singleInst += std::count(c.begin(), c.end(), ref);
    }

    // Determine how many cells the rhs is away from matching the lhs
    int commons = 0;
    for(int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // find if i,j is a common element
            if (lhs.getBoard()[i][j] == rhs.getBoard()[i][j]) {
                commons += 1;
            }
        }
    }


    return singleInst - commons;
}



// Main functions


// GETTERS ================================
HOLDER& Board::getBoard() const {
    return this->__boardConfig;
}
std::array<std::array<std::string, 3>, 3> Board::exportAsString() const {
    std::array<std::array<std::string, 3>, 3> finale;

    this->__applyToBoard([](unsigned long x, unsigned long y, std::array<States, 3>* xPointer, States* yPointer) {
        finale[x][y] = stateMap[*yPointer];
    });

    return finale;
}
std::vector<std::pair<int, int>> Board::getEmptySquares() const {
    std::vector<std::pair<int, int>> emptySquares;
    auto& cop = this->__boardConfig;

    this->__applyToBoard([](unsigned long x, unsigned long y, std::array<States, 3>* xPointer, States* yPointer) {
        if (cop[x][y] == NULL__) {
            emptySquares.emplace_back(static_cast<int>(x), static_cast<int>(y));
        }
    });

    return emptySquares;
}
std::vector<std::string> Board::getBoardVectorDump() const {
    std::vector<std::string> stateVec;
    auto& cop = this->__boardConfig;

    // Iterate over whole board
    this->__applyToBoard([](unsigned long x, unsigned long y, std::array<States, 3>* xPointer, States* yPointer){
        stateVec.push_back(Board::stateMap[cop[x][y]]);
    });

    return stateVec;
}



// SETTERS =================================
bool Board::updateBoard(std::pair<int, int> coords, Board::States value) {
    __boardConfig[coords.first][coords.second] = value;
}



// MISC ========================================
static Board::States Board::inverse(States state) {
    switch (state) {
        case(X):
            return O;
        case(O):
            return X;
        default:
            return NULL__;
    }
}
int Board::getValue(Board::States reference) const {
    // Computes the different ways the reference player can win, 2 moves away  = 1 point, 1 move away = 2 points

    // O(1) time complexity
    for (int i = 0; i < 3; i++) {

    }

}

















// Pre constructor constructors
// Hard coded winning moves
void Board::initMoves() {
    this->__winningMoves = {
            {{{W, W, W}, {L, L, L}, {L, L, L}}, {{L, L, L}, {W, W, W}, {L, L, L}}, {{L, L, L}, {L, L, L}, {W, W, W}}},
            {{{W, L, L}, {L, W, L}, {L, L, W}}, {{L, L, W}, {L, W, L}, {W, L, L}}},
            {{{W, L, L}, {W, L, L}, {W, L, L}}, {{L, W, L}, {L, W, L}, {L, W, L}}, {{L, L, W}, {L, L, W}, {L, L, W}}}
    };
}




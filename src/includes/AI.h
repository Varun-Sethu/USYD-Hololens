//
// Created by varun on 26/11/2018.
//

#ifndef TICTACTOE_AI_H
#define TICTACTOE_AI_H

#include "Board.h"
#include "structures/Tree.h"
#include <algorithm>


// Simple AI class based off min-max
class AI {
public:

    static AI& getInstance();

    Board computeBestMove(Board& board);
    Tree generateGameTree(const Board& startNode, Board::States player) const;
    Board minMax(Tree gameTree) const;







    AI(AI const&) = delete;
    void operator=(AI const&) = delete;
private:
    AI(){};
    std::vector<Tree> generateSubTreeFromBoard(const Board& target, Board::States player) const;



};


#endif //TICTACTOE_AI_H

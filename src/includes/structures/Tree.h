//
// Created by varun on 26/11/2018.
//

#ifndef TICTACTOE_TREE_H
#define TICTACTOE_TREE_H

#include <utility>
#include <list>
#include <algorithm>
#include "../Board.h"


// Tree strucutre utilised in min-max algorithm
class Tree {
public:
    // Don't need move semantics so we can leave them out
    Tree(Board board, Board::States reference);
    void insertChild(Board board, Board::States player);
    void makeChild(Tree tree);
    Board& getBoard();
    Board::States getPlayer();
    // Weird name but essentially it gives me the board with the lowest cost
    std::pair<int, Board> search();
    std::list<Tree>& getChildren();
    void replaceChildren(std::list<Tree> adoptedKids);

    ~Tree();


private:
    Tree* __parent = nullptr;
    std::list<Tree> __children;
    std::pair<int, Board> __content;
    int __heuristicValue = 0;
    Board::States __reference;

};

#endif //TICTACTOE_TREE_H

//
// Created by varun on 26/11/2018.
//

#include "../../includes/structures/Tree.h"

Tree::Tree(Board board, Board::States reference) {
    this->__content.first = board.getValue(reference);
    this->__content.second = board;
    this->__reference = reference;
}

Tree::~Tree() {
    for(Tree p: __children) {
        delete p;
    }
}

std::list<Tree>& Tree::getChildren() {
    return this->__children;
}


void Tree::insertChild(Board board, Board::States player) {
    this->__children.push_back(Tree(board, player));
}

void Tree::makeChild(Tree tree) {
    this->__children.push_back(tree);
}
Board& Tree::getBoard() {
    return this->__content.second;
}
Board::States Tree::getPlayer() {
    return this->__reference;
}
void Tree::replaceChildren(std::list<Tree> adoptedKids) {
    this->__children = adoptedKids;
}




std::pair<int, Board> Tree::search() {
    if(this->__children.empty()) {
        return std::pair<int, Board>(this->getBoard().getValue(this->getPlayer()), this->getBoard());
    }

    std::vector<std::pair<int, Board>> childHeuristics;
    for (Tree& child: this->__children) {
        childHeuristics.push_back(child.search());
    }

    // Return the child board that is the minimum of all these boards
    return *(std::min_element(childHeuristics.begin(), childHeuristics.end(), [](std::pair<int, Board> s1, std::pair<int, Board> s2){
        return s1.first > s2.first ? s1 : s2;
    }));
}



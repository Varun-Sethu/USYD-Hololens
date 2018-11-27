//
// Created by varun on 26/11/2018.
//


#include "../includes/AI.h"


static AI& AI::getInstance() {
    static AI instance;
    return instance;
}


std::vector<Tree> AI::generateSubTreeFromBoard(const Board &target, Board::States player) const {
    std::vector<Tree> children;
    // Get the available empty squares
    std::vector<std::pair<int, int>> empty = target.getEmptySquares();

    for (auto &c: empty) {
        Board instance = Board(target);
        instance.updateBoard(c, player);
        children.push_back(Tree(instance, player));
    }

    return children;

}




// Generate the full gameboard for us
Tree AI::generateGameTree(const Board &startNode, Board::States player) const {
    Tree start = Tree(startNode, player);
    // Get the available empty squares
    std::vector<std::pair<int, int>> empty = startNode.getEmptySquares();


    // Just a list that keeps track of the trees we have generate
    std::vector<Tree&> generatedChildren = {start};

    for(auto it = generatedChildren.begin(); it != generatedChildren.end(); ++it) {
        Tree current = generatedChildren[it - generatedChildren.begin()];
        std::vector<std::string> boardStates = current.getBoard().getBoardVectorDump();

        // Determine to terminate or not
        if (std::find(boardStates.begin(), boardStates.end(), " ") != boardStates.end()) {
            // This means the board is full and thus cannot generate children for this entry, this is the terminating condition
            continue;
        }

        // Generate the list of potential children
        auto children = this->generateSubTreeFromBoard(current.getBoard(), Board::inverse(current.getPlayer()));
        // Copy it into a list structure
        std::list<Tree> childCop;
        current.replaceChildren(childCop);
        std::copy(children.begin(), children.end(), std::back_inserter(current.getChildren()));
        // Push the new kids into the vector list
        generatedChildren.emplace_back(children);
    }

    return start;
}



Board AI::minMax(Tree gameTree) const {
    // perform a search on the game tree recursively
    std::pair<int, Board> best = gameTree.search();
    return best.second;
}

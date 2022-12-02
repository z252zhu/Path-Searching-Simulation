#include "mainboard.h"
#include <iostream>
#include <vector>
#include <stack>
#include <math.h>

#define vhCOST   10
#define diagCOST sqrt(2 * vhCOST * vhCOST)

struct Point {
    // 2D position
    int row;
    int col;
    // costs: f = g + h
    int g, h, f;
};

struct TreeNode {
    Point pos;
    std::vector<TreeNode *> next;
    TreeNode *root;
};


MainBoard::MainBoard()
{
    // default board dimensions
    boardWidth = 10;
    boardHeight = 10;

    // default starting and ending positions
    startPos = std::make_pair(0, 0);
    endPos = std::make_pair(boardHeight - 1, boardWidth - 1);

    // default board info
    memset(boardContent, EMPTY, sizeof(boardContent));
    boardContent[0][0] = STARTPOS;
    boardContent[boardWidth - 1][boardHeight - 1] = ENDPOS;
}

TreeNode *MainBoard::createTreeNode(Point pos) {
    TreeNode *tNew = new TreeNode;
    memset(tNew, 0, sizeof(TreeNode));
    tNew->pos.row = pos.row;
    tNew->pos.col = pos.col;
    return tNew;
}

int MainBoard::calculateH(Point cur, Point end) {
    int rowDiff = abs(cur.row - end.row);
    int colDiff = abs(cur.col - end.col);
    return vhCOST * (rowDiff + colDiff);
}

bool MainBoard::checkBond(int row, int col, int rowMax, int colMax) {
    return (row >= 0 && col >= 0 && row < rowMax && col < colMax);
}

void MainBoard::printResult(bool find, TreeNode* lastTN) {
    if (find) {
        std::cout << "Path";
        std::stack<std::pair<int, int>> res;
        while (lastTN) {
            res.push({lastTN->pos.row, lastTN->pos.col});
            lastTN = lastTN->root;
        }
        while (!res.empty()) {
            std::pair<int, int> p = res.top();
            res.pop();
            if (boardContent[p.first][p.second] != STARTPOS &&
                boardContent[p.first][p.second] != ENDPOS)
                boardContent[p.first][p.second] = PATH;
            printf(" -> (%d,%d)", p.first, p.second);
        }
        std::cout << std::endl;
    } else {
        std::cout << "Path NOT found..." << std::endl;
    }
}

void MainBoard::AStarSearch() {
    // maximum number of rows and cols
    int const ROWS = boardWidth;
    int const COLS = boardHeight;

    // set up starting and ending positions
    Point begPos = {this->startPos.first, this->startPos.second};
    Point endPos = {this->endPos.first, this->endPos.second};

    // debug
    std::cout << ROWS << "," << COLS << std::endl;
    std::cout << "Start Pos: " << begPos.row << "," << begPos.col << std::endl;
    std::cout << "End Pos: " << endPos.row << "," << endPos.col << std::endl;

    // a vector of vectors to store tried (exist) paths: 1-TRIED; 0-EMPTY
    std::vector<std::vector<bool>> existPath(ROWS, std::vector<bool>(COLS, false));

    // a TreeNode root to save possible paths
    // a vector of TreeNode to save valid moves
    TreeNode* ROOT = NULL;
    std::vector<TreeNode*> validMoves;

    // initialize the starting point as tree root
    ROOT = createTreeNode(begPos);
    ROOT->pos.g = INT_MAX;
    ROOT->pos.h = INT_MAX;
    ROOT->pos.f = INT_MAX;
    existPath[begPos.row][begPos.col] = true;
    validMoves.push_back(ROOT);

    // set up a pointer to traverce the tree
    TreeNode* currNode = ROOT;

    // possible directions around a position
    std::vector<std::pair<int, int> > dirs = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},
        {-1, -1}, {1, -1}, {-1, 1}, {1, 1},
    };

    // initiate iterators for finding the move with minimum f value
    std::vector<TreeNode*>::iterator it;
    std::vector<TreeNode*>::iterator itMin;

    while (validMoves.size()) {
        // loop through all 8 surrounding points and look for valid move
        for (int i = 0; i < dirs.size(); i++) {
            TreeNode* nextTN = createTreeNode(currNode->pos);
            // update direction parameters
            nextTN->pos.row += dirs[i].first;
            nextTN->pos.col += dirs[i].second;

            // check if the move is valid or invalid
            if (checkBond(nextTN->pos.row, nextTN->pos.col, ROWS, COLS) &&
                boardContent[nextTN->pos.row][nextTN->pos.col] != OBSTACLE &&
                existPath[nextTN->pos.row][nextTN->pos.col] == false) {
                // update parameters for next tree node
                int gAdd = ((i < 4) ? vhCOST : diagCOST);
                nextTN->pos.g = currNode->pos.g + gAdd;
                nextTN->pos.h = calculateH(nextTN->pos, endPos);
                nextTN->pos.f = nextTN->pos.g + nextTN->pos.h;
                // add/link to the main tree
                currNode->next.push_back(nextTN);
                nextTN->root = currNode;
                // add to valid moves
                validMoves.push_back(nextTN);
            } else {
                delete nextTN;
            }
        }

        // loop through valid moves and look for the move with minimum f value
        itMin = validMoves.begin();
        for (it = validMoves.begin(); it != validMoves.end(); it++) {
            itMin = (((*it)->pos.f < (*itMin)->pos.f) ? it : itMin);
        }

        // move to the point with minimum f value
        currNode = *itMin;
        existPath[currNode->pos.row][currNode->pos.col] = true;
        validMoves.erase(itMin);

        // check if the selected move reach the ending position
        if (currNode->pos.row == endPos.row &&
            currNode->pos.col == endPos.col) {
            printResult(true, currNode);
            return;
        }
    }
    // no valid move and no path found
    printResult(false, NULL);
    return;
}

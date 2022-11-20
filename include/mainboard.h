#ifndef MAINBOARD_H
#define MAINBOARD_H

#include <iostream>
#include <vector>

class Point;
class TreeNode;

class MainBoard
{
public:
    MainBoard();

    enum BLOCKTYPE {EMPTY, STARTPOS, ENDPOS,
                    OBSTACLE, PATH};

    int boardWidth;
    int boardHeight;
    BLOCKTYPE boardContent[1001][1001];
    std::pair<int, int> startPos;
    std::pair<int, int> endPos;
    void AStarSearch();

private:
    TreeNode *createTreeNode(Point pos);
    int calculateH(Point cur, Point end);
    bool checkBond(int row, int col, int rowMax, int colMax);
    void printResult(bool find, TreeNode *lastTN);
};

#endif // MAINBOARD_H

#include "renderarea.h"
#include "mainboard.h"

#include <QPainter>
#include <QtGui>
#include <QtGlobal>


RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    mainBoard = new MainBoard;
    setSizePolicy(QSizePolicy::Minimum,
                  QSizePolicy::Minimum);
    setMinimumSize(0, 200);
    setAutoFillBackground(true);
    ifSetStartPos = false;
    ifSetEndPos = false;
}

void RenderArea::setBoardWidth(const int newBoardWidth)
{
    mainBoard->boardWidth = newBoardWidth;
    update();
}

void RenderArea::setBoardHeight(const int newBoardHeight)
{
    mainBoard->boardHeight = newBoardHeight;
    update();
}

void RenderArea::setStartPos(const std::pair<int, int> newStartPos)
{
    mainBoard->startPos = newStartPos;
    update();
}

void RenderArea::setEndPos(const std::pair<int, int> newEndPos)
{
    mainBoard->endPos = newEndPos;
    update();
}

void RenderArea::startSearch()
{
    //mainBoard->clean();
    mainBoard->AStarSearch();
    update();
}

std::pair<int, int> RenderArea::getBoardDim()
{
    return std::make_pair(mainBoard->boardWidth,
                          mainBoard->boardWidth);
}


void RenderArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int rectWidth = (width() - 2) / mainBoard->boardWidth;
    int rectHeight = (height() - 2) / mainBoard->boardHeight;
    for(int i = 0; i < mainBoard->boardWidth; i++)
    {
        for(int j = 0; j < mainBoard->boardHeight; j++)
        {
            if (mainBoard->boardContent[j][i] == mainBoard->EMPTY) {
                painter.setBrush(Qt::black);
                painter.drawRect(i * rectWidth + 1, j * rectHeight + 1,
                                 rectWidth, rectHeight);
            }
            else if (mainBoard->boardContent[j][i] == mainBoard->STARTPOS) {
                painter.setBrush(Qt::green);
                painter.drawRect(i * rectWidth + 1, j * rectHeight + 1,
                                 rectWidth, rectHeight);
            }
            else if (mainBoard->boardContent[j][i] == mainBoard->ENDPOS) {
                painter.setBrush(Qt::yellow);
                painter.drawRect(i * rectWidth + 1, j * rectHeight + 1,
                                 rectWidth, rectHeight);
            }
            else if (mainBoard->boardContent[j][i] == mainBoard->OBSTACLE)
            {
                painter.setBrush(Qt::red);
                painter.drawRect(i * rectWidth + 1, j * rectHeight + 1,
                                 rectWidth, rectHeight);
            }
            else
            {
                painter.setBrush(Qt::blue);
                painter.drawRect(i * rectWidth + 1, j * rectHeight + 1,
                                 rectWidth, rectHeight);
            }
        }
    }
}

void RenderArea::changeSetStartPos()
{
    this->ifSetStartPos = true;
}

void RenderArea::changeSetEndPos()
{
    this->ifSetEndPos = true;
}

void RenderArea::mousePressEvent(QMouseEvent *event)
{
    int x = event->pos().x();
    int y = event->pos().y();
    x = qMin(x / ((width() - 2) / mainBoard->boardWidth),
             mainBoard->boardWidth - 1);
    y = qMin(y / ((height() - 2) / mainBoard->boardHeight),
             mainBoard->boardHeight - 1);

    if (event->button() == Qt::LeftButton)
    {
        if (ifSetStartPos == true)
        {
            std::pair<int, int> oldStartPos = mainBoard->startPos;
            mainBoard->boardContent[oldStartPos.first][oldStartPos.second] = MainBoard::EMPTY;
            mainBoard->startPos = std::make_pair(y, x);
            mainBoard->boardContent[y][x] = MainBoard::STARTPOS;
            ifSetStartPos = false;
        }
        else if (ifSetEndPos == true)
        {
            std::pair<int, int> oldEndPos = mainBoard->endPos;
            mainBoard->boardContent[oldEndPos.first][oldEndPos.second] = MainBoard::EMPTY;
            mainBoard->endPos = std::make_pair(y, x);
            mainBoard->boardContent[y][x] = MainBoard::ENDPOS;
            ifSetEndPos = false;
        }
        else if (mainBoard->boardContent[y][x] == MainBoard::EMPTY)
        {
            mainBoard->boardContent[y][x] = MainBoard::OBSTACLE;
        }
    }
    if (event->button() == Qt::RightButton)
    {
        if (mainBoard->boardContent[y][x] == MainBoard::OBSTACLE)
        {
            mainBoard->boardContent[y][x] = MainBoard::EMPTY;
        }
    }
    update();
}

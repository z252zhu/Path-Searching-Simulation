#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>

class MainBoard;
class QMouseEvent;

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    explicit RenderArea(QWidget *parent = nullptr);
    void changeSetStartPos();
    void changeSetEndPos();
    std::pair<int, int> getBoardDim();

public slots:
    void setBoardWidth(const int newBoardWidth);
    void setBoardHeight(const int newBoardHeight);
    void setStartPos(const std::pair<int, int> newStartPos);
    void setEndPos(const std::pair<int, int> newEndPos);
    void startSearch();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    MainBoard *mainBoard;
    bool ifSetStartPos;
    bool ifSetEndPos;
};


#endif // RENDERAREA_H

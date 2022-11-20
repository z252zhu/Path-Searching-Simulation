#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QMainWindow>

class QLabel;
class QSpinBox;
class QPushButton;
class QGridLayout;
class RenderArea;
class QMessageBox;

class MainWidget : public QMainWindow
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    RenderArea *renderArea;
    QWidget *mainWidget;
    QGridLayout *mainLayout;

    QSpinBox *boardWidthSpinBox;
    QSpinBox *boardHeightSpinBox;

    QLabel *boardWidthLabel;
    QLabel *boardHeightLabel;
    //QLabel *boundaryHintLabel;
    //QLabel *userMouseHintLabel;

    QPushButton *pbSetWidth;
    QPushButton *pbSetHeight;
    QPushButton *pbSearch;
    QPushButton *pbStartPos;
    QPushButton *pbEndPos;
    QPushButton *pbAddObs;
    QPushButton *pbRemoveObs;
    QPushButton *pbInfo;

private slots:
    void boardWidthChanged();
    void boardHeightChanged();
    void pbStartPosClicked();
    void pbEndPosClicked();
    void pbSearchClicked();
    void pbInfoClicked();
};

#endif // MAINWIDGET_H

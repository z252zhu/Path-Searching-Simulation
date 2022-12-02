#include "mainwidget.h"
#include "renderarea.h"
#include <iostream>
#include <QtWidgets>


MainWidget::MainWidget(QWidget *parent)
    : QMainWindow(parent)
{
    // Main window setups
    setWindowTitle("Path Searching Algorithm");
    this->resize(600,600);
    mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);
    renderArea = new RenderArea;

    // QPushButton
    pbSearch = new QPushButton(tr("Start Searching"));
    pbStartPos = new QPushButton(tr("Starting Position"));
    pbEndPos = new QPushButton(tr("Ending Position"));
    pbInfo = new QPushButton(tr("Click for Info"));

    // QSpinBox and QLabel
    boardWidthSpinBox = new QSpinBox;
    boardWidthSpinBox->setRange(1, 500);
    boardWidthSpinBox->setValue(renderArea->getBoardDim().first);
    boardWidthSpinBox->setSpecialValueText(tr("1 (Set Width)"));
    boardWidthLabel = new QLabel(tr("Board Width (1~500):"));
    boardWidthLabel->setBuddy(boardWidthSpinBox);

    boardHeightSpinBox = new QSpinBox;
    boardHeightSpinBox->setRange(1, 500);
    boardHeightSpinBox->setValue(renderArea->getBoardDim().second);
    boardHeightSpinBox->setSpecialValueText(tr("1 (Set Height)"));
    boardHeightLabel = new QLabel(tr("Board Height (1~500):"));
    boardWidthLabel->setBuddy(boardHeightSpinBox);

    //boundaryHintLabel = new QLabel(tr("(RANGE: MIN: 1 ~ MAX: 500)"));
    //userMouseHintLabel = new QLabel(tr("(Left/Right click BOARD to add/remove a obstacle)"));

    // connect widgets to functions
    connect(boardWidthSpinBox, &QSpinBox::valueChanged, this, &MainWidget::boardWidthChanged);
    connect(boardHeightSpinBox, &QSpinBox::valueChanged, this, &MainWidget::boardHeightChanged);
    connect(pbStartPos, &QPushButton::clicked, this, &MainWidget::pbStartPosClicked);
    connect(pbEndPos, &QPushButton::clicked, this, &MainWidget::pbEndPosClicked);
    connect(pbSearch, &QPushButton::clicked, this, &MainWidget::pbSearchClicked);
    connect(pbInfo, &QPushButton::clicked, this, &MainWidget::pbInfoClicked);

    // main grid layout
    mainLayout = new QGridLayout(mainWidget);
    mainLayout->addWidget(renderArea, 0, 0, 1, 5);
    mainLayout->addWidget(boardWidthLabel, 2, 0);
    mainLayout->addWidget(boardWidthSpinBox, 2, 1);
    mainLayout->addWidget(boardHeightLabel, 2, 2);
    mainLayout->addWidget(boardHeightSpinBox, 2, 3);
    //mainLayout->addWidget(boundaryHintLabel, 2, 4);
    mainLayout->addWidget(pbStartPos, 3, 0);
    mainLayout->addWidget(pbEndPos, 3, 1);
    mainLayout->addWidget(pbSearch, 3, 2);
    mainLayout->addWidget(pbInfo, 3, 3);
    //mainLayout->addWidget(userMouseHintLabel, 3, 3);
}

MainWidget::~MainWidget()
{
}

void MainWidget::boardWidthChanged()
{
    int boardWidth = boardWidthSpinBox->value();
    renderArea->setBoardWidth(boardWidth);
    std::cout << boardWidth << std::endl;
}

void MainWidget::boardHeightChanged()
{
    int boardHeight = boardHeightSpinBox->value();
    renderArea->setBoardHeight(boardHeight);
    std::cout << boardHeight << std::endl;
}

void MainWidget::pbStartPosClicked()
{
    renderArea->changeSetStartPos();
    std::cout << "start" << std::endl;
}

void MainWidget::pbEndPosClicked()
{
    renderArea->changeSetEndPos();
    std::cout << "end" << std::endl;
}

void MainWidget::pbSearchClicked()
{
    renderArea->startSearch();
    std::cout << "search" << std::endl;
}

void MainWidget::pbInfoClicked()
{
    QString message = tr("Range for Width/Height: (1~500). \n"
                         "Left-click to Add a obstacle. \n"
                         "Reft-click to Remove a obstacle. \n");
    QMessageBox::information(this, tr("User Manual"), message);
    std::cout << "info" << std::endl;
}

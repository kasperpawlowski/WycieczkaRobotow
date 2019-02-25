#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "situationscene.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

    view_      = new QGraphicsView(this);
    formation_ = new FormationKeypad(10, 10, this);
    path_      = new ScratchpadController(this);
    simulationControlButton_ = new QPushButton(this);

    mainLayout_ = new QGridLayout();
    mainLayout_->addWidget(view_, 0, 0, 3, 1);
    mainLayout_->addWidget(formation_, 2, 1);
    mainLayout_->addWidget(path_, 1, 1);
    mainLayout_->addWidget(simulationControlButton_, 0, 1);
    ui_->centralWidget->setLayout(mainLayout_);
    showMaximized();

    situation_ = new SituationScene(view_, this);
}

MainWindow::~MainWindow()
{
    delete mainLayout_;
    delete ui_;
}

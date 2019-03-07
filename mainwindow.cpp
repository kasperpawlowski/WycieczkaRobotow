#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow),
    simulationStarted_(false)
{
    ui_->setupUi(this);

    // create all the widgets
    view_      = new QGraphicsView(this);
    formation_ = new FormationKeypad(10, 10, this);
    path_      = new ScratchpadController(this);
    simulationControlButton_ = new QPushButton(this);

    // create a QGraphicsScene that will be connected to QGraphicsView
    situation_ = new SituationScene(view_, this);

    // create a layout for all the widgets
    mainLayout_ = new QGridLayout();
    mainLayout_->addWidget(view_, 0, 0, 3, 1);
    mainLayout_->addWidget(formation_, 2, 1);
    mainLayout_->addWidget(path_, 1, 1);
    mainLayout_->addWidget(simulationControlButton_, 0, 1);
    ui_->centralWidget->setLayout(mainLayout_);

    connect(simulationControlButton_, SIGNAL(clicked()), this, SLOT(updateSimulationState()));
    connect(situation_, SIGNAL(simulationFinishAnnouncement()), this, SLOT(updateSimulationState()));
    refreshSimulationControlButton();
}

MainWindow::~MainWindow()
{
    delete mainLayout_;
    delete ui_;
}

void MainWindow::updateSimulationState()
{
    if(simulationStarted_)
    {
        simulationStarted_ = false;
        emit SimulationStopRequest();
    }
    else
    {
        simulationStarted_ = true;
        emit SimulationStartRequest(situation_);
    }
    refreshSimulationControlButton();
}

void MainWindow::refreshSimulationControlButton()
{
    if(simulationStarted_)
    {
        simulationControlButton_->setText("Simulation started (click again to STOP)");
        simulationControlButton_->setStyleSheet("background-color: rgb(0, 255, 0); color: rgb(0, 0, 0)");
    }
    else
    {
        simulationControlButton_->setText("Start simulation");
        simulationControlButton_->setStyleSheet("");
    }
}
